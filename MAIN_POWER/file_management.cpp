#include "file_management.hpp"

void clear_file(const char* measFile) {
    if (!SPIFFS.begin()) {
        Serial.println("[FILE_MGT] Error iniciando SPIFFS");
        return;
    }

    File file = SPIFFS.open(measFile, "w");
    if (!file) {
        Serial.println("[FILE_MGT] Error abriendo el fichero para borrar");
        return;
    }

    file.close();
    Serial.println("[FILE_MGT] El contenido del fichero ha sido borrado.");
}

void read_meas(const char* measFile){
    if (!SPIFFS.begin()) {
        Serial.println("[FILE_MGT] Error iniciando SPIFFS");
        return;
    }

    File measurementFile = SPIFFS.open(measFile, "r");
    if (!measurementFile) {
        Serial.println("[FILE_MGT] Error abriendo fichero");
        return;
    }

    Serial.println("[FILE_MGT] Abriendo " + String(measFile) + ". Contenido: ");

    while (measurementFile.available()) {
        Serial.write(measurementFile.read());
    }

    measurementFile.close();
}

bool write_meas(const char* measFile, telemetry_t measures, String timestamp) {
    if (!SPIFFS.begin()) {
        return false;
    }

    File measurementFile = SPIFFS.open(measFile, "a");
    if (!measurementFile) {
        return false;
    }

    String measurement = timestamp +
                         " VPanelSolar: " + String(measures.VSolar) + " V, " +
                         "IPanelSolar: " + String(measures.ISolar) + " mA, " +
                         "VBatBackup: " + String(measures.VBatbu) + " V, " +
                         "IBatBackup: " + String(measures.IBatbu) + " mA, " +
                         "VBat1: " + String(measures.VBat1) + " V, " +
                         "IBat1: " + String(measures.IBat1) + " mA, " +
                         "VBat2: " + String(measures.VBat2) + " V, " +
                         "IBat2: " + String(measures.IBat2) + " mA";

    measurementFile.println(measurement);
    measurementFile.close();

    return true;
}
