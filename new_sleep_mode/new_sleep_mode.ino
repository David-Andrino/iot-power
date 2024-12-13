#include "new_sleep_mode.hpp"

#define SLEEP_TIME 10000

void setup() {
  Serial.begin(9600);
  WiFi.begin("POC", "cacacaca");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);
  Serial.println("Entering in Sleep Mode");
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  Serial.flush();
  setSleepMode(SLEEP_TIME);
  
  exitSleepMode();
  Serial.println("Exit from Sleep Mode");

}

void loop() {
  // put your main code here, to run repeatedly:

}
