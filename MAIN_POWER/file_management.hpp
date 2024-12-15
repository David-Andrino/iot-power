/*! \file write_file.h
    \brief Fichero de cabecera del 
*/

// TODO: Comentar este fichero

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <FS.h>
#include <time.h>
#include "telemetry.hpp"

extern void clear_file(const char* measFile);
extern void read_meas(const char* measFile);
extern bool write_meas(const char* measFile , telemetry_t measures, String timestamp);

#endif
