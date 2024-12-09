#include "INA_medidas.h"
#include "mqtt_client.hpp"

#define ssid "POC"
#define password "cacacaca"

float VSolar = 1, ISolar = 2, VBatbu = 3, IBatbu = 4, VBat1 = 5, IBat1 = 6, VBat2 = 7, IBat2 = 8;
telemetry_t telemetry = {VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2};

void setup() {
    Serial.begin(9600);
    while (!Serial);
    setup_wifi();
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
    // Print telemetry data
    Serial.print("VSolar [V]: "); Serial.println(telemetry.VSolar);
    Serial.print("ISolar [mA]: "); Serial.println(telemetry.ISolar);
    Serial.print("VBatbu [V]: "); Serial.println(telemetry.VBatbu);
    Serial.print("IBatbu [mA]: "); Serial.println(telemetry.IBatbu);
    Serial.print("VBat1 [V]: "); Serial.println(telemetry.VBat1);
    Serial.print("IBat1 [mA]: "); Serial.println(telemetry.IBat1);
    Serial.print("VBat2 [V]: "); Serial.println(telemetry.VBat2);
    Serial.print("IBat2 [mA]: "); Serial.println(telemetry.IBat2);

    if (WiFi.status() == WL_CONNECTED){
      if (!publishTelemetry(const_cast<char*>("192.168.111.69"), 4444, telemetry)){
        Serial.println("ERROR: MQTT no disponible");
      }
    }else{
        Serial.println("ERROR: Wifi no disponible");
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
  int i=0;
  while (WiFi.status() != WL_CONNECTED && i!=20) {
    delay(500);
    Serial.print(".");
    i++;
  }
  if(i!=20){
    Serial.println("");
    Serial.println("WiFi connected");
  }else{
    Serial.println("");
    Serial.println("WiFi disconnected");    
  }
}
