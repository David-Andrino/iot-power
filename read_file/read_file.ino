#include "file_management.hpp"

const char* testFile = "/measurements.txt";

void setup() {
  Serial.begin(9600);
  Serial.println("[LOG_MGR] Envie 'b' o 'd' para borrar el archivo y 'r' o 'l' para leerlo ");
}

void loop() {
    // Verificar si hay datos disponibles en el puerto serial
    if (Serial.available() > 0) {
        char command = Serial.read(); // Leer el carácter ingresado
        if (command == 'b' ||  command == 'd') {

            Serial.println("[LOG_MGR]Borrando contenido del archivo...");
            clear_file(testFile);

            // Confirmar estado del archivo después de borrarlo
            File file = SPIFFS.open(testFile, "r");
            if (file && file.available()) {
                Serial.println("[LOG_MGR] El archivo aún tiene contenido.");
            } else {
                Serial.println("[LOG_MGR] El archivo está vacío.");
            }
            file.close();
        } else if (command == 'r' ||  command == 'l') {
            read_meas(testFile); 
        } else if (command != '\n') {
          Serial.println("[LOG_MGR] Envie 'b' o 'd' para borrar el archivo y 'r' o 'l' para leerlo ");
        }
    }
}
