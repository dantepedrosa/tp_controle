/**
 * @file encoder.cpp
 * @brief Implementacao das funcoes declaradas em encoder.h
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#include "encoder.h"
#include "config.h"
#include <Arduino.h>

volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
float lastRPM = 0.0f;

void setupEncoderPins() {
    pinMode(PIN_ENCODER_A, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B, INPUT_PULLUP);
}

void setupEncoderInterrupt() {
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), encoderISR, RISING);
}

void IRAM_ATTR encoderISR() {
    pulseCount++;
}

unsigned long getPulseCount() {
    return pulseCount;
}

void resetPulseCount() {
    noInterrupts();
    pulseCount = 0;
    interrupts();
}

float getRPM() {
    unsigned long now = millis();
    if (now - lastTime >= (unsigned long)(Ts * 1000)) {
        noInterrupts();
        unsigned long pulses = pulseCount;
        pulseCount = 0;
        interrupts();

        lastRPM = (float)pulses * (60.0f / Ts) / (float)PULSES_PER_REV;
        lastTime = now;
    }
    return lastRPM;
}

void filterRPM() {
    const float alpha = 0.1f;
    lastRPM = alpha * lastRPM + (1.0f - alpha) * getRPM();
}
