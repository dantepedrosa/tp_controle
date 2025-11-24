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
    pinMode(PIN_MOTOR_A_EN, OUTPUT);
    pinMode(PIN_MOTOR_A_IN1, OUTPUT);
    pinMode(PIN_MOTOR_A_IN2, OUTPUT);

    pinMode(PIN_MOTOR_B_EN, OUTPUT);
    pinMode(PIN_MOTOR_B_IN1, OUTPUT);
    pinMode(PIN_MOTOR_B_IN2, OUTPUT);

    digitalWrite(PIN_MOTOR_A_EN, LOW);
    digitalWrite(PIN_MOTOR_A_IN1, LOW);
    digitalWrite(PIN_MOTOR_A_IN2, LOW);

    digitalWrite(PIN_MOTOR_B_EN, LOW);
    digitalWrite(PIN_MOTOR_B_IN1, LOW);
    digitalWrite(PIN_MOTOR_B_IN2, LOW);
}

void setMotorSpeedA(int pwmValue) {
    bool direction = (pwmValue >= 0);
    int pwm = abs(pwmValue);
    if (pwm > 255) pwm = 255;

    digitalWrite(PIN_MOTOR_A_IN1, direction ? HIGH : LOW);
    digitalWrite(PIN_MOTOR_A_IN2, direction ? LOW : HIGH);
    analogWrite(PIN_MOTOR_A_EN, pwm);
}

void setMotorSpeedB(int pwmValue) {
    bool direction = (pwmValue >= 0);
    int pwm = abs(pwmValue);
    if (pwm > 255) pwm = 255;

    digitalWrite(PIN_MOTOR_B_IN1, direction ? HIGH : LOW);
    digitalWrite(PIN_MOTOR_B_IN2, direction ? LOW : HIGH);
    analogWrite(PIN_MOTOR_B_EN, pwm);
}

void sendStepInput(int pwmValue) {
    setMotorSpeedA(pwmValue);
    setMotorSpeedB(pwmValue);
}

void stopMotors() {
    analogWrite(PIN_MOTOR_A_EN, 0);
    analogWrite(PIN_MOTOR_B_EN, 0);
}
