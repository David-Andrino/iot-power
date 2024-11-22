#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
// Replace the next variables with your SSID/Password combination
#define ssid "POC"
#define password "cacacaca"

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "192.168.238.69";

char result[256];
double VSolar = 30, ISolar = 18, VBatbu = 10, IBatbu = 22, VBat1 = 77, IBat1 = 88, VBat2 = 99, IBat2 = 123;

WiFiClient wifiClient;
WiFiUDP ntpUDP;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 4444);
  client.setCallback(callback);


}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Cliente","Cliente","Cliente")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("v1/devices/me/telemetry");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  snprintf(result, sizeof(result), "VSolar=%.2f,ISolar=%.2f,VBatbu=%.2f,IBatbu=%.2f,VBat1=%.2f,IBat1=%.2f,VBat2=%.2f,IBat2=%.2f", VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2);
  client.publish("VSolar" ,result);

}
