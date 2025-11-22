/**
 * @file config_test.ino
 * @brief Teste de configuração para verificar se as definições em config.h estão corretas.
 */

#include "config.h"

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Placa detectada: " BOARD_NAME);
}

void loop() {
    // Nada a fazer no loop
}