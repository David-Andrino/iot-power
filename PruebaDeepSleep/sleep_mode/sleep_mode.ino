
void setup() {
  Serial.begin(9600);
  Serial.println("Entra en modo sleep");
  delay(5000);
  ESP.deepSleep(5e6);
}

void loop() {
  // put your main code here, to run repeatedly:

}
