#ifndef SLEEP_H
#define SLEEP_H
#include <ESP8266WiFi.h>

extern void setSleepMode(int time_delay);
extern void exitSleepMode(String ssdi, String psw);

#endif 
