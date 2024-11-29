#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "mqtt_client.hpp"


// Credenciales WIFI
#define ssid "David's A55"
#define password "izquierdorpi"


// // Credenciales servidor MQTT
// const char* mqtt_server = "192.168.88.69";
// const int mqtt_port = 4444;

// Datos medidos por los sensores
float VSolar = 1, ISolar = 2, VBatbu = 3, IBatbu = 4, VBat1 = 5, IBat1 = 6, VBat2 = 7, IBat2 = 8;
telemetry_t telemetry = {VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2};

// // Creación del cliente WiFi y MQTT
// WiFiClient wifiClient;
// WiFiUDP ntpUDP;
// PubSubClient client(wifiClient);

/**
 * @brief Configuración del serial y conexión mediante WiFi y MQTT
 *
 * Se inicia la conexión con el serial
 * Se establece la conexión WiFi utilizando las credenciales correspondientes
 * Se establece la conexión MQTT utilizando las credenciales correspondientes
 */
void setup() {
  Serial.begin(9600);

  setup_wifi();
  // client.setServer(mqtt_server, mqtt_port);
}

/**
 * @brief Bucle principal que envía las medidas realizadas por los diferentes
 * sensores al servidor MQTT.
 */
void loop() {
  // if (!client.connected()) {
  //   reconnect();
  // }
  // postTelemetry(VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2);
  if (!publishTelemetry("192.168.88.69", 4444, telemetry)){
    Serial.println("ERROR");
  }
  delay(1000);
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

// /**
//  * @brief Realiza la conexión con el servidor MQTT.
//  * En caso de que la conexión no sea exitosa, se reinteta cada 5 segundos
//  * hasta que la conexión se realice de manera correcta.
//  */
// void reconnect() {
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection to ");
//     Serial.print(String(mqtt_server));
//     Serial.print(":");
//     Serial.println(mqtt_port);
//     if (client.connect("Cliente","Cliente","Cliente")) {
//       Serial.println("connected");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }

// /**
//  * @brief Crea la estructura del mensaje para realizar la publicación de las
//  * medidas tomadas, en el servidor MQTT para mostralos en el ThingsBoard cada
//  * segundo.
//  */
// void postTelemetry (float VSolar, float ISolar, float VBatbu, float IBatbu, float VBat1, float IBat1, float VBat2, float IBat2){
//   char result[256];
//   if (!client.connected()) {
//     reconnect();
//   }
//   snprintf(result, sizeof(result), "{VSolar:%.2f,ISolar:%.2f,VBatbu:%.2f,IBatbu:%.2f,VBat1:%.2f,IBat1:%.2f,VBat2:%.2f,IBat2:%.2f}", VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2);
//   bool statusPublish = client.publish("v1/devices/me/telemetry" ,result);
//   if (!statusPublish){
//     Serial.println("ERROR: the data can`t be pusblished");
//   }
//   client.disconnect();
// }
