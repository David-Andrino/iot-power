#ifndef MQTT_CLIENT_HPP
#define MQTT_CLIENT_HPP
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "telemetry.hpp"

/**
 * @brief Crea el cliente MQTT y establece la conexión con el servidor MQTT.
 * Además, define la estructura del mensaje para publicar las medidas
 * tomadas y mostrarlas en ThingsBoard. En caso de que ocurra un error
 * en la conexión con el servidor MQTT, se reintentará cada 5 segundos
 * mediante una espera bloqueante.
 * @param mqtt_server Dirección del servidor MQTT.
 * @param mqtt_port Puerto del servidor MQTT.
 * @param telemetry Referencia a una estructura que contiene las medidas de telemetría.
 * @return true si la publicación de telemetría fue exitosa, false en caso contrario.
 */
extern bool publishTelemetry(char* mqtt_server, int mqtt_port, telemetry_t& telemetry);

#endif
