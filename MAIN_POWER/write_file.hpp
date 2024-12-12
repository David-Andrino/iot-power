/*! \file write_file.h
    \brief Fichero de cabecera del
*/

#ifndef WRITE_FILE_HPP
#define WRITE_FILE_HPP

#include <FS.h>
#include <time.h>

/**
 * @brief Estructura con las medidas tomadas por los diferentes sensores
 */
typedef struct {
    float VSolar;  /**< Tensión panel solar */
    float ISolar;  /**< Corriente panel solar */
    float VBatbu;  /**< Tensión batería backup */
    float IBatbu;  /**< Corriente batería backup */
    float VBat1;   /**< Tensión batería 1 */
    float IBat1;   /**< Corriente batería 1 */
    float VBat2;   /**< Tensión batería 2 */
    float IBat2;   /**< Corriente batería 2 */
} telemetry_t;

extern bool write_meas(const char* measFile , telemetry_t measures, String timestamp);

#endif