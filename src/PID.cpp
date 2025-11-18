#include "PID.h"

PID::PID(float kp, float ki, float kd)
  : _kp(kp), _ki(ki), _kd(kd), _minOut(-255), _maxOut(255), _integral(0), _lastError(0), _lastTime(0) {}

void PID::setTunings(float kp, float ki, float kd) {
  _kp = kp; _ki = ki; _kd = kd;
}

void PID::setOutputLimits(float minOut, float maxOut) {
  _minOut = minOut; _maxOut = maxOut;
}

float PID::compute(float error) {
  unsigned long now = millis();
  float dt = 0.0;
  if (_lastTime == 0) dt = 0.0; else dt = (now - _lastTime) / 1000.0;

  if (dt <= 0.0) dt = 1e-3;

  _integral += error * dt;
  float derivative = (error - _lastError) / dt;

  float out = _kp * error + _ki * _integral + _kd * derivative;
  if (out > _maxOut) out = _maxOut;
  if (out < _minOut) out = _minOut;

  _lastError = error;
  _lastTime = now;
  return out;
}
