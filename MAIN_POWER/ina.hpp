/*! \file ina.h
    \brief Fichero cabecera de ina.c
    
    Contamos con la librería INA226_WE cuya documentación puede ser accedida en:
    https://github.com/wollewald/INA226_WE?tab=readme-ov-file
*/

/*! \def I2C_D_PANEL
    \brief Indica la dirección I2C del INA que toma las medidas del panel solar.
*/
/*! \def I2C_D_BAT_BU
    \brief Indica la dirección I2C del INA que toma las medidas de la batería de BackUp.
*/
/*! \def I2C_D_BAT_1
    \brief Indica la dirección I2C del INA que toma las medidas de la primera batería.
*/
/*! \def I2C_D_BAT_2
    \brief Indica la dirección I2C del INA que toma las medidas de la segunda batería.
*/

/*! \fn void measureINA226(telemetry_t *telemetry)
    \brief Lee las medidas de los INAS y modifica las almacena la dirección de puntero indicada.
    \param telemetry Dirección de puntero de la estructura que almacena todas las medidas de tensión y corriente de las baterias y panel solar.
*/
#ifndef ina_h
#define ina_h

//Librerías utilizadas
#include <Wire.h>
#include <INA226_WE.h>
#include "telemetry.hpp"

// Direcciones I2C
#define I2C_D_PANEL  0x45
#define I2C_D_BAT_BU 0x40
#define I2C_D_BAT_1  0x44
#define I2C_D_BAT_2  0x41


// Funciones

/**************************************************************************//**
 * \brief Realiza una medida de todos los sensores.
 *
 *Inicialmente se verifica si se ha realizado la configuración inicial de los INAs.
 *  -Si se ha realizado, se despiertan y reconfiguran
 *  -En caso contrario se realiza una configuración inicial antes de la captación de datos.
 *Se realiza 1 medida que es almacenada en la estrucutra de datos.
 *Y finalmente se ponen a bajo consumo los INA.
 * \param telemetry Puntero a la estructura de datos que contiene las medidas de tensión y corriente de las baterias y panel solar.
 ******************************************************************************/
void measureINA226(telemetry_t *telemetry);

#endif
