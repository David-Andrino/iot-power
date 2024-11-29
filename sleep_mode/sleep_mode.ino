#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "mqtt_client.hpp"

// Credenciales WIFI
#define ssid "David's A55"
#define password "izquierdorpi"

// Datos medidos por los sensores
float VSolar = 10, ISolar = 20, VBatbu = 30, IBatbu = 40, VBat1 = 50, IBat1 = 60, VBat2 = 70, IBat2 = 80;
telemetry_t telemetry = {VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2};
void setup() {
  Serial.begin(9600);
  setup_wifi();
  if (!publishTelemetry("192.168.88.69", 4444, telemetry)){
    Serial.println("ERROR");
  }
  ESP.deepSleep(5e6);
}

void loop() {
  // put your main code here, to run repeatedly:

}

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
