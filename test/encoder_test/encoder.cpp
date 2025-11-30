#include "encoder.h"
#include "config.h"
#include <Arduino.h>

// Precisam ser exatamente o mesmo tipo do .h
volatile unsigned long pulseCountA = 0;
volatile unsigned long pulseCountB = 0;

void setupEncoderPins() {
    pinMode(PIN_ENCODER_A, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B, INPUT_PULLUP);
}

void setupEncoderInterrupts() {
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), encoderISRA, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), encoderISRB, RISING);
}

unsigned long getPulseCountA() { return pulseCountA; }
unsigned long getPulseCountB() { return pulseCountB; }

void resetPulseCountA() { pulseCountA = 0; }
void resetPulseCountB() { pulseCountB = 0; }

// ISR — MUST MATCH THE TYPE
#if defined(ESP32)
void IRAM_ATTR encoderISRA() { pulseCountA++; }
void IRAM_ATTR encoderISRB() { pulseCountB++; }
#else
void encoderISRA() { pulseCountA++; }
void encoderISRB() { pulseCountB++; }
#endif

// Pulsos no intervalo Ts (metodologia BIA-Kit)
int getSpeedA() {
    unsigned long pulses = pulseCountA;
    pulseCountA = 0;
    return pulses;
}

int getSpeedB() {
    unsigned long pulses = pulseCountB;
    pulseCountB = 0;
    return pulses;
}
