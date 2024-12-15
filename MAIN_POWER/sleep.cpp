#include "sleep.hpp"

#include <ESP8266WiFi.h>

void sleep_low_power(int time_delay, String ssid, String psw) {
    Serial.println("[SLEEP] Entrando en modo bajo consumo");
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    system_update_cpu_freq(SYS_CPU_80MHZ);

    delay(time_delay);

    Serial.println("[SLEEP] Saliendo del modo bajo consumo");
    system_update_cpu_freq(SYS_CPU_160MHZ);
    WiFi.forceSleepWake();
    delay(1);
    WiFi.mode(WIFI_STA);

    // No hace falta conectar a la red WiFi, ya que se conectará en el loop
}
