#include "write_file.hpp"

// Implementación de la función
bool write_meas(const char* measFile, telemetry_t measures, String timestamp) {
    if (!SPIFFS.begin()) {
        return false;
    }

    File measurementFile = SPIFFS.open(measFile, "a");
    if (!measurementFile) {
        return false;
    }

    String measurement = timestamp +
                         " VPanelSolar: " + String(measures.VSolar) + "V, " +
                         "IPanelSolar: " + String(measures.ISolar) + "mA, " +
                         "VBatBackup: " + String(measures.VBatbu) + "V, " +
                         "IBatBackup: " + String(measures.IBatbu) + "mA, " +
                         "VBat1: " + String(measures.VBat1) + "V, " +
                         "IBat1: " + String(measures.IBat1) + "mA, " +
                         "VBat2: " + String(measures.VBat2) + "V, " +
                         "IBat2: " + String(measures.IBat2) + "mA";

    measurementFile.println(measurement);
    measurementFile.close();

    return true;
}
