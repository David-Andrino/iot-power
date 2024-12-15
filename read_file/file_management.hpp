/** @file file_management.h
    @brief Módulo de manejo de ficheros
*/

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <FS.h>
#include <time.h>
#include "telemetry.hpp"

/**
 * @brief Borra el contenido del fichero indicado.
 * 
 * @param measFile Nombre del fichero a borrar.
 */
extern void clear_file(const char* measFile);

/**
 * @brief Lee el contenido del fichero indicado. Imprime en consola el contenido.
 * 
 * @param measFile Nombre del fichero a leer.
 */
extern void read_meas(const char* measFile);

/**
 * @brief Escribe la medida en el fichero indicado.
 * Formato: [timestamp] VPanelSolar: X.XX V, IPanelSolar: X.XX mA, VBatBackup: X.XX V, IBatBackup: X.XX mA, VBat1: X.XX V, IBat1: X.XX mA, VBat2: X.XX V, IBat2: X.XX mA
 * 
 * @param measFile Nombre del fichero.
 * @param measures Medidas a escribir.
 * @param timestamp Marca de tiempo.
 * @return true si la escritura fue exitosa, false en caso contrario.
 */
extern bool write_meas(const char* measFile , telemetry_t measures, String timestamp);

#endif
