#include "Encoder.h"

volatile long Encoder::_pulses = 0;
uint8_t Encoder::_pinForAttach = 255;

Encoder::Encoder(uint8_t pin) : _pin(pin) {}

void Encoder::begin() {
  _pinForAttach = _pin;
  pinMode(_pin, INPUT_PULLUP);
  // OBS: usa uma interrupção simples por flanco
  attachInterrupt(digitalPinToInterrupt(_pin), Encoder::isr, RISING);
}

long Encoder::getPulses() {
  noInterrupts();
  long p = _pulses;
  interrupts();
  return p;
}

void Encoder::reset() {
  noInterrupts();
  _pulses = 0;
  interrupts();
}

float Encoder::getDistanceMeters() {
  long pulses = getPulses();
  float rev = (float)pulses / (float)PULSES_PER_REV;
  float circumference = 3.14159265 * WHEEL_DIAMETER_M;
  return rev * circumference;
}

void Encoder::isr() {
  _pulses++;
}
