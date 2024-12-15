#include "sleep.hpp"

extern void setSleepMode(int time_delay){
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
  Serial.println("WiFi is down");
  system_update_cpu_freq(SYS_CPU_80MHZ);
  delay(time_delay);

}

extern void exitSleepMode(String ssdi, String psw){
  system_update_cpu_freq(SYS_CPU_160MHZ);
  WiFi.forceSleepWake();
  delay(1);
  // Bring up the WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssdi, psw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
