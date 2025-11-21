/**
 * @file motor_test.ino
 * @brief Teste completo do robo: direita, esquerda e reto, variando PWM e medindo o RPM via encoder.
 *
 * Fluxo do teste:
 *  1. Liga motor para DIREITA (pwm positivo)
 *  2. Liga motor para ESQUERDA (pwm negativo)
 *  3. Liga motor RETO (pwm positivo moderado)
 *  Tudo automatico, com leitura de RPM a cada Ts.
 *
 * @date nov de 2025
 * @author Dante Jun…
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// valores de PWM que serao testados em sequencia
int pwmValues[] = {80, 120, 160, 200, 255};
int pwmIndex = 0;

enum TestState { GO_RIGHT, GO_LEFT, GO_STRAIGHT };
TestState state = GO_RIGHT;

unsigned long timerPWM = 0;
const unsigned long stepTime = 4000;  // troca de estado a cada 4s

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando teste do robo...");
    Serial.println("Placa detectada: " BOARD_NAME);

    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupt();
}

void loop() {
    // gerenciamento de mudanca de estado (direita -> esquerda -> reto)
    if (millis() - timerPWM >= stepTime) {
        timerPWM = millis();
        pwmIndex++;
        if (pwmIndex >= (int)(sizeof(pwmValues) / sizeof(int))) {
            pwmIndex = 0;
            state = (TestState)((state + 1) % 3);  // muda estado
        }
        resetPulseCount();
    }

    // selecao da direcao conforme estado atual
    int pwmCommand = pwmValues[pwmIndex];
    switch (state) {
        case GO_RIGHT:
            pwmCommand = abs(pwmCommand);    // positivo
            break;
        case GO_LEFT:
            pwmCommand = -abs(pwmCommand);   // negativo = girar para lado oposto
            break;
        case GO_STRAIGHT:
            pwmCommand = abs(pwmCommand);    // positivo, mas indicando "modo reto"
            break;
    }

    // aplica PWM ao motor
    setMotorSpeed(pwmCommand);

    // leitura do RPM atual
    float rpm = getRPM();

    // impressao no serial
    Serial.print("ESTADO = ");
    if (
