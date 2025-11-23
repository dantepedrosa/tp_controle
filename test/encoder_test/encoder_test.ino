/**
 * @file encoder_test.cpp
 * @brief Teste unitario do encoder: contagem de pulsos e calculo de RPM.
 *
 * @date nov de 2025
 * @author ...
 */

#include <Arduino.h>
#include "config.h"
#include "encoder.h"

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando teste do ENCODER...");

    setupEncoderPins();
    setupEncoderInterrupt();

    Serial.println("Movimente o eixo do motor manualmente ou gire a roda.");

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
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);}

void loop() {
    float rpm = getRPM();
    unsigned long pulses = getPulseCount();

    Serial.print("Pulsos = ");
    Serial.print(pulses);
    Serial.print(" | RPM = ");
    Serial.println(rpm);

    delay(100);
}
