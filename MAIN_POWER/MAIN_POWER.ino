#include "telemetry.hpp"
#include "hardware.hpp"
#include "ina.hpp"
#include "mqtt_client.hpp"
#include "file_management.hpp"
#include "sleep.hpp"

#define ssid "POC"
#define password "cacacaca"

#define timeSleep 2000
#define wifiTries 35
#define BatTh     11.5
#define SolarTh   20

#define DEBUG

int sw_bck_in, sw_bck_out = 0;
float VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2 = 0;
telemetry_t telemetry = {VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2};
char timeStr[50] = "";
struct tm currentTime;

void setup_wifi(int tries);

void setup() {

    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
    Serial.begin(9600);
    while (!Serial);
    telemetry.VSolar=0;
    telemetry.ISolar=0;
    telemetry.VBatbu=0;
    telemetry.IBatbu=0;
    telemetry.VBat1=0;
    telemetry.IBat1=0;
    telemetry.VBat2=0;
    telemetry.IBat2=0;

}

void loop() {
    //Si no se inicializan los INA el sistema se bloquea
    measureINA226(&telemetry);
    #ifdef DEBUG
      // Print telemetry data
      Serial.print("VSolar [V]: "); Serial.println(telemetry.VSolar);
      Serial.print("ISolar [mA]: "); Serial.println(telemetry.ISolar);
      Serial.print("VBatbu [V]: "); Serial.println(telemetry.VBatbu);
      Serial.print("IBatbu [mA]: "); Serial.println(telemetry.IBatbu);
      Serial.print("VBat1 [V]: "); Serial.println(telemetry.VBat1);
      Serial.print("IBat1 [mA]: "); Serial.println(telemetry.IBat1);
      Serial.print("VBat2 [V]: "); Serial.println(telemetry.VBat2);
      Serial.print("IBat2 [mA]: "); Serial.println(telemetry.IBat2);
    #endif

    setRelays(&telemetry);

    setup_wifi(wifiTries);

    if (WiFi.status() == WL_CONNECTED){
      getLocalTime(&currentTime, 1000);
      strftime(timeStr, 50, "[%d/%m/%y - %H:%M:%S]", &currentTime);

      if (!publishTelemetry(const_cast<char*>("192.168.111.69"), 4444, telemetry)){
        #ifdef DEBUG
          Serial.println("ERROR: MQTT no disponible");
        #endif
      }else{
        #ifdef DEBUG
          Serial.println("Medidas enviadas con éxito");
        #endif
      }
    }

    if (write_meas("/measurements.txt", telemetry, timeStr)){
      #ifdef DEBUG
        Serial.println("Fichero escrito con exito");
      #endif
    } else {
      #ifdef DEBUG
        Serial.println("ERROR: El fichero no ha podido ser escrito");
      #endif
    }

    #ifdef DEBUG
      Serial.println("Entering in Sleep Mode");
    #endif

    setSleepMode(timeSleep);

    #ifdef DEBUG
      Serial.println("Exit from Sleep Mode");
    #endif

    exitSleepMode(ssid,password);
}

/**
 * @brief Realiza la conexión WiFi mediante las credenciales correspondientes.
 * Sino es exitosa, se reintenta hasta que se conecte.
 */
void setup_wifi(int tries) {
  delay(10);
  #ifdef DEBUG
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  #endif

  WiFi.begin(ssid, password);
  int i=0;
  while (WiFi.status() != WL_CONNECTED && i!=tries) {
    delay(500);
    #ifdef DEBUG
      Serial.print(".");
    #endif
    i++;
  }
  if(i!=tries){
    #ifdef DEBUG
      Serial.println("");
      Serial.println("WiFi connected");
    #endif
  }else{
    #ifdef DEBUG
      Serial.println("");
      Serial.println("WiFi disconnected");
    #endif
  }

  configTime(3600, 0, "time.nist.gov", "0.pool.ntp.org");
}

void setRelays(telemetry_t *telemetry){
  if (telemetry->VSolar > SolarTh) {
    digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);  
  }else if(telemetry->VBatbu>BatTh){
    digitalWrite(D7,HIGH);
    digitalWrite(D8,HIGH);
  }else{
    digitalWrite(D7,LOW);
    digitalWrite(D8,LOW);
  }
  
}
