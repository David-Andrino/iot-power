#include "read_file.hpp"

void setup() {
  Serial.begin(9600);
  read_meas("/measurements.txt");

}

void loop() {
    // Verificar si hay datos disponibles en el puerto serial
    if (Serial.available() > 0) {
        char command = Serial.read(); // Leer el carácter ingresado

        if (command == 'b') {
            const char* testFile = "/measurements.txt";

            Serial.println("Borrando contenido del archivo...");
            clear_file(testFile);

            // Confirmar estado del archivo después de borrarlo
            File file = SPIFFS.open(testFile, "r");
            if (file && file.available()) {
                Serial.println("El archivo aún tiene contenido:");
                while (file.available()) {
                    Serial.write(file.read());
                }
            } else {
                Serial.println("El archivo está vacío.");
            }
            file.close();
        }
    }
}
