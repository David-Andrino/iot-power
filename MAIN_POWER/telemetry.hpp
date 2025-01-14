/**
 * @file telemetry.hpp
 * @author David Andrino
 * @author Estela Mora
 * @author Hugo Sánchez
 * @author Fernando Sanz
 * @brief Definición de la estructura de telemetría
 * @version 1.1
 * @date 15-12-2024
 */
#ifndef TELEMETRY_H
#define TELEMETRY_H

/**
 * @brief Estructura con las medidas tomadas por los diferentes sensores
 */
typedef struct {
    float VSolar;  /**< Tension panel solar */
    float ISolar;  /**< Corriente panel solar */
    float VBatbu;  /**< Tension bateria backup */
    float IBatbu;  /**< Corriente bateria backup */
    float VBat1;   /**< Tension bateria 1 */
    float IBat1;   /**< Corriente bateria 1 */
    float VBat2;   /**< Tension bateria 2 */
    float IBat2;   /**< Corriente bateria 2 */
} telemetry_t;

#endif