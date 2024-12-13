/*! \file write_file.h
    \brief Fichero de cabecera del
*/

#ifndef WRITE_FILE_HPP
#define WRITE_FILE_HPP

#include <FS.h>
#include <time.h>
#include "mqtt_client.hpp"

extern bool write_meas(const char* measFile , telemetry_t measures, String timestamp);

#endif
