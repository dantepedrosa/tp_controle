/**
 * @file test_straight_line.ino
 * @brief Controle em linha reta com modelo de 1a ordem.
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// ===== PWM BASE =====
const int PWM_BASE = 200;
const float Ts_ms = Ts * 1000.0;

// ===== GANHOS PI =====
float Kp = 1.0;
float Ki = 15.0;

// controle
float e = 0, e_prev = 0, corr = 0;

// tempo
unsigned long lastT = 0;

// prototipos
float predictRPM_A(int pwm);
float predictRPM_B(int pwm);

// codigo das tabelas e interpolacao inserido aqui...

// ===== PREDIÇÃO COM BASE NO MODELO =====
float predictRPM_A(int pwm) {
    float K, T;
    interpModel(modelA, sizeof(modelA)/sizeof(MotorModel), pwm, K, T);
    return K; // regime permanente
}

float predictRPM_B(int pwm) {
    float K, T;
    interpModel(modelB, sizeof(modelB)/sizeof(MotorModel), pwm, K, T);
    return K; // regime permanente
}

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();

    Serial.println("time_ms,rpmA,rpmB,predA,predB,pwmA,pwmB,corr");
}

void loop() {
    unsigned long now = millis();
    if (now - lastT < Ts_ms) return;
    lastT = now;

    // ===== LEITURA =====
    int pA = getSpeedA();
    int pB = getSpeedB();

    float rpmA = (float)pA * (60.0f / Ts) / PULSES_PER_REV;
    float rpmB = (float)pB * (60.0f / Ts) / PULSES_PER_REV;

    // ===== PREVISAO DO MODELO =====
    float rpmA_model = predictRPM_A(PWM_BASE);
    float rpmB_model = predictRPM_B(PWM_BASE);

    // erro real + erro previsto
    float e_model = rpmA_model - rpmB_model;
    float e_real  = rpmA - rpmB;

    // erro total utilizado no PI
    e = e_real + e_model;

    // ===== PI DIFERENCIAL =====
    corr += Kp * (e - e_prev) + Ki * Ts * e;
    e_prev = e;

    // limitar correcao
    if (corr > 80) corr = 80;
    if (corr < -80) corr = -80;

    // PWM resultante
    int pwmA = PWM_BASE - corr;
    int pwmB = PWM_BASE + corr;

    // nao permitir inverter sentido
    if (pwmA < 0) pwmA = 0;
    if (pwmB < 0) pwmB = 0;
    if (pwmA > 255) pwmA = 255;
    if (pwmB > 255) pwmB = 255;

    // aplica
    setMotorSpeedA(pwmA);
    setMotorSpeedB(pwmB);

    // debug
    Serial.print(now); Serial.print(",");
    Serial.print(rpmA); Serial.print(",");
    Serial.print(rpmB); Serial.print(",");
    Serial.print(rpmA_model); Serial.print(",");
    Serial.print(rpmB_model); Serial.print(",");
    Serial.print(pwmA); Serial.print(",");
    Serial.print(pwmB); Serial.print(",");
    Serial.println(corr);
}
