#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>

#define MSG_BUFFER_SIZE (50)

WiFiClient wifiClient;
WiFiUDP ntpUDP;
PubSubClient mqttClient(wifiClient);

const char* ssid = "YOUR-WIFI";
const char* password = "YOUR-WIFI-PSK";
const char* mqtt_server = "BROKER"; // eg. your-demo.cedalo.cloud or 192.168.1.11
const uint16_t mqtt_server_port = 1883; // or 8883 most common for tls transport
const char* mqttUser = "user";
const char* mqttPassword = "pass";
const char* mqttTopicIn = "esp-8266-in";
const char* mqttTopicOut = "esp-8266-out";


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
#ifdef MQTT_TLS
  wifiClient.setInsecure();
#endif
  Serial.println("WiFi connected");
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: '");
  Serial.print(topic);
  Serial.print("' with payload: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String mensaje = "Jeje Holiwis";
  mqttClient.publish(mqttTopicOut,(" ESP8266-Time: " + mensaje).c_str());
}


void connect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    String mqttClientId = "";
    if (mqttClient.connect(mqttClientId.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected");
      mqttClient.subscribe(mqttTopicIn);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" will try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(115200);
  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_server_port);
  mqttClient.setCallback(callback);
}


void loop() {
  if (!mqttClient.connected()) {
    connect();
  }
 
  mqttClient.loop();
}
