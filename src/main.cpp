/**
 * @file test_straight_line.ino
 * @brief Controle para andar em linha reta usando controle diferencial.
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// ===== PARAMETROS =====
const int PWM_BASE = 200;         // PWM nominal para andar para frente
const float Ts_ms = Ts * 1000.0;  // tempo de amostragem

// ===== CONTROLADOR PI DIFERENCIAL =====
// Controla: erro = rpmA - rpmB
float Kp = 2.0;
float Ki = 20.0;

float e = 0, e_prev = 0;
float corr = 0;                   // correcao no PWM

unsigned long lastControl = 0;

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);

    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();

    Serial.println("time_ms,rpmA,rpmB,PWM_A,PWM_B,corr");
}

void loop() {
    unsigned long now = millis();
    if (now - lastControl < Ts_ms) return;
    lastControl = now;

    // ===== LEITURA =====
    int pA = getSpeedA();
    int pB = getSpeedB();

    float rpmA = (float)pA * (60.0f / Ts) / (float)PULSES_PER_REV;
    float rpmB = (float)pB * (60.0f / Ts) / (float)PULSES_PER_REV;

    // ===== ERRO DIFERENCIAL =====
    e = rpmA - rpmB;

    // PI
    corr += Kp * (e - e_prev) + Ki * Ts * e;
    e_prev = e;

    // saturacao da correcao
    if (corr > 80) corr = 80;
    if (corr < -80) corr = -80;

    // PWM dos motores
    int pwmA = PWM_BASE - corr;
    int pwmB = PWM_BASE + corr;

    // limita para nao permitir valores negativos
    if (pwmA < 0) pwmA = 0;
    if (pwmB < 0) pwmB = 0;
    if (pwmA > 255) pwmA = 255;
    if (pwmB > 255) pwmB = 255;

    // aplica
    setMotorSpeedA(pwmA);
    setMotorSpeedB(pwmB);

    // ===== DEBUG =====
    Serial.print(now);
    Serial.print(",");
    Serial.print(rpmA);
    Serial.print(",");
    Serial.print(rpmB);
    Serial.print(",");
    Serial.print(pwmA);
    Serial.print(",");
    Serial.print(pwmB);
    Serial.print(",");
    Serial.println(corr);
}
