#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "config.h"

class Encoder {
public:
  Encoder(uint8_t pin);
  void begin();
  long getPulses();
  void reset();
  float getDistanceMeters();
  static void isr();
private:
  uint8_t _pin;
  static volatile long _pulses;
  static uint8_t _pinForAttach;
};

#endif
