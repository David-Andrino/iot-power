#include "write_file.hpp"

// Implementación de la función
bool write_meas(const char* measFile, telemetry_t measures, time_t timestamp) {
    if (!SPIFFS.begin()) {
        return false;
    }

    File measurementFile = SPIFFS.open(measFile, "a");
    if (!measurementFile) {
        return false;
    }

    char timeStr[50];
    struct tm* timeInfo = localtime(&timestamp);
    strftime(timeStr, sizeof(timeStr), "[%d/%m/%y - %H:%M:%S]", timeInfo);

    String measurement = String(timeStr) +
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
