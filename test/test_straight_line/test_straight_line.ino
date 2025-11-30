/**
 * @file test_straight_line.ino
 * @brief Controle em malha fechada para andar em linha reta (2WD).
 * Usa getSpeedA/B (metodo BIA) → converte para RPM.
 * 
 * @date nov de 2025
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// ===== PARAMETROS =====
const float RPM_SETPOINT = 8.0;
const float Ts_ms = Ts * 1000.0;   // tempo de amostragem em ms

// ===== GANHOS PI (ajuste fino depois) =====
float Kp_A = 0.8, Ki_A = 4.5;
float Kp_B = 0.8, Ki_B = 5.0;

// ===== VARIAVEIS DE CONTROLE =====
float eA = 0, eA_prev = 0, uA = 0;
float eB = 0, eB_prev = 0, uB = 0;

unsigned long lastControlTime = 0;

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();

    Serial.println("time_ms,rpmA,rpmB,uA,uB");
}

void loop() {
    unsigned long now = millis();
    if (now - lastControlTime < Ts_ms) return;
    lastControlTime = now;

    // ===== LEITURA DOS PULSOS =====
    int pulsesA = getSpeedA();
    int pulsesB = getSpeedB();

    // ===== CONVERTE PARA RPM =====
    float rpmA = (float)pulsesA * (60.0f / Ts) / (float)PULSES_PER_REV;
    float rpmB = (float)pulsesB * (60.0f / Ts) / (float)PULSES_PER_REV;

    // ===== CALCULO DO ERRO =====
    eA = RPM_SETPOINT - rpmA;
    eB = RPM_SETPOINT - rpmB;

    // ===== CONTROLADOR PI =====
    uA += Kp_A * (eA - eA_prev) + Ki_A * Ts * eA;
    uB += Kp_B * (eB - eB_prev) + Ki_B * Ts * eB;

    eA_prev = eA;
    eB_prev = eB;

    // saturacao
    if (uA > 255) uA = 255;
    if (uA < -255) uA = -255;
    if (uB > 255) uB = 255;
    if (uB < -255) uB = -255;

    // ===== APLICA =====
    setMotorSpeedA((int)uA);
    setMotorSpeedB((int)uB);

    // ===== DEBUG =====
    Serial.print(now);
    Serial.print(",");
    Serial.print(rpmA);
    Serial.print(",");
    Serial.print(rpmB);
    Serial.print(",");
    Serial.print(uA);
    Serial.print(",");
    Serial.println(uB);
}
