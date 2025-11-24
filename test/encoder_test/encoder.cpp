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

volatile unsigned long pulseCountA = 0;
volatile unsigned long pulseCountB = 0;

static unsigned long lastTimeA = 0;
static unsigned long lastTimeB = 0;

static float lastRPMA = 0;
static float lastRPMB = 0;

void setupEncoderPins() {
    pinMode(PIN_ENCODER_A_A, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B_A, INPUT_PULLUP);

    pinMode(PIN_ENCODER_A_B, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B_B, INPUT_PULLUP);
}

void setupEncoderInterrupts() {
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A_A), encoderISRA, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A_B), encoderISRB, RISING);
}

void IRAM_ATTR encoderISRA() {
    pulseCountA++;
}

void IRAM_ATTR encoderISRB() {
    pulseCountB++;
}

float getRPMA() {
    unsigned long now = millis();
    unsigned long dt = now - lastTimeA;

    if (dt >= Ts * 1000) {
        lastRPMA = (pulseCountA * (60000.0f / dt)) / PULSES_PER_REV;
        lastTimeA = now;
        pulseCountA = 0;
    }
    return lastRPMA;
}

float getRPMB() {
    unsigned long now = millis();
    unsigned long dt = now - lastTimeB;

    if (dt >= Ts * 1000) {
        lastRPMB = (pulseCountB * (60000.0f / dt)) / PULSES_PER_REV;
        lastTimeB = now;
        pulseCountB = 0;
    }
    return lastRPMB;
}

unsigned long getPulseCountA() {
    return pulseCountA;
}

unsigned long getPulseCountB() {
    return pulseCountB;
}

void resetPulseCountA() {
    pulseCountA = 0;
}

void resetPulseCountB() {
    pulseCountB = 0;
}
