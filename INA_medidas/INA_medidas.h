/*! \file INA_medidas.h
    \brief Fichero cabecera de INA_medidas.c
    
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



#ifndef ina_medidas_h
#define ina_medidas_h

//Librerías utilizadas
#include <Wire.h>
#include <INA226_WE.h>

// Direcciones I2C
#define I2C_D_PANEL  0x40
#define I2C_D_BAT_BU 0x40
#define I2C_D_BAT_1  0x40
#define I2C_D_BAT_2  0x40

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

// Funciones
void measureINA226(telemetry_t *telemetry);

#endif
