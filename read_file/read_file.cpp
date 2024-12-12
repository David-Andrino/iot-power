#include "read_file.hpp"

extern void read_meas(const char* measFile){
    if (!SPIFFS.begin()) {
        Serial.println("Error iniciando SPIFFS");
        return;
    }

    File measurementFile = SPIFFS.open(measFile, "r");
    if (!measurementFile) {
        Serial.println("Error abriendo fichero");
        return;
    }

    Serial.println("");
    Serial.print("Contenido del fichero ");
    Serial.println(measFile);

    while (measurementFile.available()) {
        Serial.write(measurementFile.read());
    }

    measurementFile.close();
}

extern void clear_file(const char* measFile) {
    if (!SPIFFS.begin()) {
        Serial.println("Error iniciando SPIFFS");
        return;
    }

    File file = SPIFFS.open(measFile, "w");
    if (!file) {
        Serial.println("Error abriendo el fichero para borrar");
        return;
    }

    Serial.println("El contenido del fichero ha sido borrado.");
    file.close();
}