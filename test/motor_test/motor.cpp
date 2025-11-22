/**
 * @file motor.cpp
 * @brief Implementacao das funcoes declaradas em motor.h
 * @date nov de 2025
 *@author Dante Junqueira Pedrosa
 *@author Joao Monte…
 *@author Samantha…
 *@author Felipe…
 */

#include "motor.h"
#include "config.h"
#include <Arduino.h>

void setupMotorPins() {
    pinMode(PIN_MOTOR_PWM, OUTPUT);
    pinMode(PIN_MOTOR_DIR, OUTPUT);
    digitalWrite(PIN_MOTOR_PWM, LOW);
    digitalWrite(PIN_MOTOR_DIR, LOW);
}

void setMotorSpeed(int pwmValue) {
    bool direction = (pwmValue >= 0);
    int pwm = abs(pwmValue);
    if (pwm > 255) pwm = 255;

    digitalWrite(PIN_MOTOR_DIR, direction ? HIGH : LOW);
    analogWrite(PIN_MOTOR_PWM, pwm);
}

void sendStepInput(int pwmValue) {
    setMotorSpeed(pwmValue);
}
