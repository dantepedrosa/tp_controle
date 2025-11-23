/**
 * @file config_test.ino
 * @brief Teste de configuração para verificar se as definições em config.h estão corretas
 *        e piscar o LED builtin a cada 1 segundo.
 */

#include "config.h"

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Placa detectada: " BOARD_NAME);

    // REMOVER COM CIRCUITO - Pisca o LED builtin para indicar que o loop esta rodando
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

void loop() {
    // Sem loop
}