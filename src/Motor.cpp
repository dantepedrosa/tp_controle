#include "../include/Motor.h"

Motor::Motor(uint8_t pwmPin, uint8_t in1, uint8_t in2)
  : _pwm(pwmPin), _in1(in1), _in2(in2) {}

void Motor::begin() {
  pinMode(_pwm, OUTPUT);
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  // Ajustes específicos para ESP8266 PWM
#if defined(ESP8266)
  analogWriteRange(255); // usa 0..255 para PWM
  analogWriteFreq(1000); // 1 kHz por padrão
#endif
  stop();
}

void Motor::setSpeed(int speed) {
  // speed: -255 .. 255
  if (speed > 0) {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    analogWrite(_pwm, speed);
  } else if (speed < 0) {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    analogWrite(_pwm, -speed);
  } else {
    stop();
  }
}

void Motor::stop() {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
  analogWrite(_pwm, 0);
}
