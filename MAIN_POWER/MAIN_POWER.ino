#include "INA_medidas.h"
#include "mqtt_client.hpp"

#define ssid "David's A55"
#define password "izquierdorpi"

float VSolar = 1, ISolar = 2, VBatbu = 3, IBatbu = 4, VBat1 = 5, IBat1 = 6, VBat2 = 7, IBat2 = 8;
telemetry_t telemetry = {VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2};

void setup() {
    Serial.begin(9600);
    while (!Serial);
    setup_wifi();
}

void loop() {
    // Measure and store values in the telemetry struct
    measureINA226(&telemetry);
    // Print telemetry data
    Serial.print("VSolar [V]: "); Serial.println(telemetry.VSolar);
    Serial.print("ISolar [mA]: "); Serial.println(telemetry.ISolar);
    Serial.print("VBatbu [V]: "); Serial.println(telemetry.VBatbu);
    Serial.print("IBatbu [mA]: "); Serial.println(telemetry.IBatbu);
    Serial.print("VBat1 [V]: "); Serial.println(telemetry.VBat1);
    Serial.print("IBat1 [mA]: "); Serial.println(telemetry.IBat1);
    Serial.print("VBat2 [V]: "); Serial.println(telemetry.VBat2);
    Serial.print("IBat2 [mA]: "); Serial.println(telemetry.IBat2);
    if (!publishTelemetry(const_cast<char*>("192.168.88.69"), 4444, telemetry)){
      Serial.println("ERROR");
    }
    Serial.println("Espera 5s");
    for (int i = 0; i < 5; i++) {
        Serial.print(".");
        delay(1000);
    }
}

/**
 * @brief Realiza la conexión WiFi mediante las credenciales correspondientes.
 * Sino es exitosa, se reintenta hasta que se conecte.
 */
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}
