#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>

#define MSG_BUFFER_SIZE (50)
#define ssid "POC"
#define password "cacacaca"


WiFiClient wifiClient;
WiFiUDP ntpUDP;
PubSubClient mqttClient(wifiClient);

const char* mqtt_server = "192.168.238.69"; // eg. your-demo.cedalo.cloud or 192.168.1.11
const uint16_t mqtt_server_port = 4444; // or 8883 most common for tls transport
const char* mqttTopicIn = "GGG3XocFtPy6XXWiOWDc";
const char* mqttTopicOut = "esp-8266-out";
double VSolar = 30, ISolar = 18, VBatbu = 10, IBatbu = 22, VBat1 = 77, IBat1 = 88, VBat2 = 99, IBat2 = 123;
char result[256];

void setup() {
  Serial.begin(9600);
  Serial.println("InitCOM");
  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_server_port);
  mqttClient.setCallback(callback);

}

void loop() {
  if (!mqttClient.connected()) {
    //Si no se conecta se almacena. Internamente.
    Serial.println("NO se conecta");
    connect();
  }else{
    
    //Serial.println("Se conecta");
    //setup_wifi();
    snprintf(result, sizeof(result), "VSolar=%.2f,ISolar=%.2f,VBatbu=%.2f,IBatbu=%.2f,VBat1=%.2f,IBat1=%.2f,VBat2=%.2f,IBat2=%.2f", VSolar, ISolar, VBatbu, IBatbu, VBat1, IBat1, VBat2, IBat2);
    mqttClient.publish(mqttTopicOut,result);
    //Almacenar todo el rato.
    
  }
}


void setup_wifi() {
  delay(10);
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
  Serial.println(WiFi.localIP());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: '");
  Serial.print(topic);
  Serial.print("' with payload: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String mensaje = "Conexión inicial realizada.";
  mqttClient.publish(mqttTopicOut,(" ESP8266: " + mensaje).c_str());
}


void connect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    String mqttClientId = "tenant";
    if (mqttClient.connect("Cliente","Cliente","Cliente")) {
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
