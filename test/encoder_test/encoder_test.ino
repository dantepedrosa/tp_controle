/**
 * @file encoder_test.cpp
 * @brief Teste unitario do encoder: contagem de pulsos e calculo de RPM.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#include <Arduino.h>
#include "config.h"
#include "encoder.h"

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando teste dos ENCODERS...");

    setupEncoderPins();
    setupEncoderInterrupts();   // (mudou para ativar A e B)

    Serial.println("Gire manualmente as rodas ou mova os motores.");

    // LED VISUAL DE TESTE (pode remover depois)
    pinMode(PIN_LED_DEBUG, OUTPUT);
    digitalWrite(PIN_LED_DEBUG, HIGH);
    delay(1000);
    digitalWrite(PIN_LED_DEBUG, LOW);
}

void loop() {
    float rpmA = getRPMA();
    float rpmB = getRPMB();

    unsigned long pulsesA = getPulseCountA();
    unsigned long pulsesB = getPulseCountB();

    Serial.print("[ENCODER A] Pulsos = ");
    Serial.print(pulsesA);
    Serial.print(" | RPM = ");
    Serial.println(rpmA);

    Serial.print("[ENCODER B] Pulsos = ");
    Serial.print(pulsesB);
    Serial.print(" | RPM = ");
    Serial.println(rpmB);

    delay(100);
}