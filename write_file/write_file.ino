#include "write_file.hpp"
#include <time.h>

telemetry_t measures = {12,13,14,15,16,17,18,19};
time_t currentTime  = 1733938102;

void setup() {
  Serial.begin(9600);
  delay(1000);
  if (write_meas("/measurements.txt", measures, currentTime )){
   Serial.print("De locos");
  } else {
    Serial.print("Cagada");
  }
}

void loop() {
}
