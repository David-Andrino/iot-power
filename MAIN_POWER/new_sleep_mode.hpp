#ifndef NEW_SLEEP_MODE_HPP
#define NEW_SLEEP_MODE_HPP
#include <ESP8266WiFi.h>
#include "mqtt_client.hpp"

extern void setSleepMode(int time_delay);
extern void exitSleepMode(String ssdi, String psw);

#endif 
