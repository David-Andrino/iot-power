#include "mqtt_client.hpp"

static void reconnect(PubSubClient& client, char* const mqtt_server, int mqtt_port);


bool publishTelemetry(char* const mqtt_server, int mqtt_port, telemetry_t& telemetry){
    WiFiClient wifiClient;
    WiFiUDP ntpUDP;
    PubSubClient client(wifiClient);
    client.setServer(mqtt_server, mqtt_port);
    bool statusPublish=false;
    char result[256];
    if (!client.connected()){
      reconnect(client, mqtt_server, mqtt_port);
    }
    snprintf(result, sizeof(result), "{VSolar:%.2f,ISolar:%.2f,VBatbu:%.2f,IBatbu:%.2f,VBat1:%.2f,IBat1:%.2f,VBat2:%.2f,IBat2:%.2f}", 
    telemetry.VSolar, telemetry.ISolar, telemetry.VBatbu, telemetry.IBatbu, telemetry.VBat1, telemetry.IBat1, telemetry.VBat2, telemetry.IBat2);
    statusPublish = client.publish("v1/devices/me/telemetry" ,result);
    client.disconnect();
    return statusPublish;
}

void reconnect(PubSubClient& client, char* const mqtt_server, int mqtt_port) {
  int j=0;
  while (!client.connected() && j!=3) {
    Serial.print("Attempting MQTT connection to ");
    Serial.print(String(mqtt_server));
    Serial.print(":");
    Serial.println(mqtt_port);
    if (client.connect("Cliente","Cliente","Cliente")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 0.5 seconds");
      delay(500);
      j++;
    }
  }
}
