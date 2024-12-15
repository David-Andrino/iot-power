/**
 * @file sleep.hpp
 * @author David Andrino
 * @author Estela Mora
 * @author Hugo Sánchez
 * @author Fernando Sanz
 * @brief Módulo de bajo consumo
 * @version 1.1
 * @date 15-12-2024
 */
#ifndef SLEEP_H
#define SLEEP_H

/**
 * @brief Pone al ESP8266 en modo de bajo consumo durante el tiempo que se le indique
 * 
 * @param time_delay Tiempo en milisegundos que el ESP8266 estará en modo de bajo consumo
 */
extern void sleep_low_power(int time_delay);

#endif 
