 /**
 * @file ina.hpp
 * @author Estela Mora
 * @author David Andrino
 * @author Hugo Sánchez
 * @author Fernando Sanz
 * @brief Módulo de medida de sensores INA226
 * @version 1.1
 * @date 15-12-2024
 */
#ifndef ina_h
#define ina_h

#include <Wire.h>
#include <INA226_WE.h>
#include "telemetry.hpp"

/** @def I2C_D_PANEL
    @brief Indica la dirección I2C del INA que toma las medidas del panel solar.
*/
#define I2C_D_PANEL  0x45
/** @def I2C_D_BAT_BU
    @brief Indica la dirección I2C del INA que toma las medidas de la batería de BackUp.
*/
#define I2C_D_BAT_BU 0x40
/** @def I2C_D_BAT_1
    @brief Indica la dirección I2C del INA que toma las medidas de la primera batería.
*/
#define I2C_D_BAT_1  0x44
/** @def I2C_D_BAT_2
    @brief Indica la dirección I2C del INA que toma las medidas de la segunda batería.
*/
#define I2C_D_BAT_2  0x41

/**
 * @brief Realiza una medida de todos los sensores.
 *
 * Inicialmente se verifica si se ha realizado la configuración inicial de los INAs.
 *     - Si se ha realizado, se despiertan y reconfiguran.
 *     - En caso contrario se realiza una configuración inicial antes de la captación de datos.
 * Se realiza 1 medida que es almacenada en la estructura de datos.
 * Finalmente se apagan los INA.
 * 
 * @param telemetry Puntero a la estructura de datos que contiene las medidas.
 */
void measureINA226(telemetry_t *telemetry);

#endif
