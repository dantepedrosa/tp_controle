/**
 * @file encoder.h
 * @brief Interface para leitura do encoder e contagem de pulsos.
 */

#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// Contadores globais — tipo padronizado
extern volatile unsigned long pulseCountA;
extern volatile unsigned long pulseCountB;

void setupEncoderPins();
void setupEncoderInterrupts();

int  getSpeedA();
int  getSpeedB();

void resetPulseCountA();
void resetPulseCountB();

unsigned long getPulseCountA();
unsigned long getPulseCountB();

#if defined(ESP32)
    void IRAM_ATTR encoderISRA();
    void IRAM_ATTR encoderISRB();
#else
    void encoderISRA();
    void encoderISRB();
#endif

#endif
