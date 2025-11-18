#ifndef SIMPLE_PID_H
#define SIMPLE_PID_H

#include <Arduino.h>

class PID {
public:
  PID(float kp, float ki, float kd);
  void setTunings(float kp, float ki, float kd);
  void setOutputLimits(float minOut, float maxOut);
  float compute(float input); // input = error (setpoint - measurement) here
private:
  float _kp, _ki, _kd;
  float _minOut, _maxOut;
  float _integral;
  float _lastError;
  unsigned long _lastTime;
};

#endif
