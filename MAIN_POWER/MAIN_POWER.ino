#include "telemetry.hpp"
#include "hardware.hpp"
#include "ina.hpp"
#include "mqtt_client.hpp"
#include "file_management.hpp"
#include "sleep.hpp"

#define DEBUG

#ifdef DEBUG
#define PRINT_DEBUG(...) Serial.println(__VA_ARGS__)
#else
#define PRINT_DEBUG(...)
#endif

#define ssid             "POC"
#define password         "cacacaca"

#define MQTT_SERVER      const_cast<char*>("192.168.111.69")
#define MQTT_PORT        4444

#define TIME_SLEEP       2000
#define WIFI_TRIES       35
#define BAT_THRESH       11.5
#define SOLAR_THRESH     20
#define MEASUREMENT_FILE "/measurements.txt"

telemetry_t telemetry   = {0, 0, 0, 0, 0, 0, 0, 0};
char        timeStr[50] = "";
struct tm   currentTime;

/**
 * @brief Intenta realizar la conexión WiFi hasta WIFI_TRIES intentos
 */
static void setup_wifi();

/**
 * @brief Conmuta los relés en función de las medidas tomadas
 * 
 * 1. Si la tensión del panel solar es mayor que SOLAR_THRESH, se activa el panel solar.
 * 2. Si la tensión de la batería de backup es mayor que BAT_THRESH, se activa la batería de backup.
 * 3. En caso contrario, se activa la protección de sobredescarga.
 * 
 * @param telemetry Puntero a la estructura de medidas
 */
static void setRelays(telemetry_t *telemetry){

void setup() {
    pinMode(RELAY_SW_IN,  OUTPUT);
    pinMode(RELAY_SW_OUT, OUTPUT);
    pinMode(SDA,          OUTPUT);
    pinMode(SCL,          OUTPUT);

    Serial.begin(9600);
}

void loop() {
    measureINA226(&telemetry); // Si no están los INA conectados, bloquea

    PRINT_DEBUG("[INA] VSolar [V]:  " + String(telemetry.VSolar));
    PRINT_DEBUG("[INA] ISolar [mA]: " + String(telemetry.ISolar));
    PRINT_DEBUG("[INA] VBatbu [V]:  " + String(telemetry.VBatbu));
    PRINT_DEBUG("[INA] IBatbu [mA]: " + String(telemetry.IBatbu));
    PRINT_DEBUG("[INA] VBat1 [V]:   " + String(telemetry.VBat1));
    PRINT_DEBUG("[INA] IBat1 [mA]:  " + String(telemetry.IBat1));
    PRINT_DEBUG("[INA] VBat2 [V]:   " + String(telemetry.VBat2));
    PRINT_DEBUG("[INA] IBat2 [mA]:  " + String(telemetry.IBat2));

    setRelays(&telemetry);

    setup_wifi();

    if (WiFi.status() == WL_CONNECTED){
        configTime(3600, 0, "time.nist.gov", "0.pool.ntp.org");
        
        if (!publishTelemetry(MQTT_SERVER, MQTT_PORT, telemetry)){
            PRINT_DEBUG("[POWER] ERROR publicando medidas");
        } else {
            PRINT_DEBUG("[POWER] Medidas publicadas con éxito");
        }

        getLocalTime(&currentTime, 1000);
        strftime(timeStr, 50, "[%d/%m/%y - %H:%M:%S]", &currentTime);
        PRINT_DEBUG("[WIFI] Sincronizado con NTP. Hora obtenida: " + String(timeStr));
    } else {
        PRINT_DEBUG("[WIFI] No se ha podido conectar a la red WiFi");
        snprintf(timeStr, 50, "[00/00/00 - 00:00:00]")
    }

    if (write_meas(MEASUREMENT_FILE, telemetry, timeStr)){
        PRINT_DEBUG("[POWER] Fichero escrito con exito");
    } else {
        PRINT_DEBUG("[POWER] El fichero no ha podido ser escrito");
    }

    sleep_low_power(TIME_SLEEP);
}

static void setup_wifi() {
    delay(10);
    Serial.print("[WIFI] Intentando conectar a " + ssid);

    WiFi.begin(ssid, password);
    for (int i = 0; i < WIFI_TRIES && WiFi.status() != WL_CONNECTED; i++) {
        delay(500);
        Serial.print(".");
        i++;
    }
    if(WiFi.status() == WL_CONNECTED){
        PRINT_DEBUG("[WIFI] Conectado a la red WiFi " + ssid + " con IP: " + WiFi.localIP());
    } else {
        PRINT_DEBUG("[WIFI] No se ha podido conectar a la red WiFi");
    }
}

static void setRelays(telemetry_t *telemetry){
    if (telemetry->VSolar > SOLAR_THRESH) {
        PRINT_DEBUG("[RELAY] Panel solar activo");

        digitalWrite(RELAY_SW_IN,LOW);
        digitalWrite(RELAY_SW_OUT,LOW);  
    } else if (telemetry->VBatbu > BAT_THRESH){
        PRINT_DEBUG("[RELAY] Bateria backup activa");

        digitalWrite(RELAY_SW_IN,HIGH);
        digitalWrite(RELAY_SW_OUT,HIGH);
    } else {
        PRINT_DEBUG("[RELAY] Activando protección sobredescarga. Se detendrá el sistema");

        digitalWrite(RELAY_SW_IN,LOW);
        digitalWrite(RELAY_SW_OUT,LOW);
    }
}
