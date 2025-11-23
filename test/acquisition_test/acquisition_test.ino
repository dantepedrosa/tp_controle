/**
 * @file acquisition_test.ino
 * @brief Coleta de dados para modelagem (funcao de transferencia).
 * 
 * Aplica degraus de PWM e registra (tempo, PWM, RPM) via Serial.
 * Ideal para MATLAB/Python -> estimar sistema 1a ou 2a ordem.
 *
 * @date nov de 2025
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"
#include "data_logger.h"  // opcional — se quiser salvar CSV automaticamente

// Arrays de PWM que serao testados experimentalmente
int pwmSteps[] = {80, 120, 160, 200, 240};
int pwmIndex = 0;

unsigned long stepStartTime = 0;
const unsigned long stepDuration = 5000; // 5s por degrau

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando acquisition_test...");

    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupt();
    setupLogger();        // cabecalho CSV via Serial

    // REMOVER COM CIRCUITO - Pisca o LED builtin para indicar que o loop esta rodando
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

void loop() {
    // troca de degrau a cada 5s
    if (millis() - stepStartTime >= stepDuration) {
        stepStartTime = millis();
        pwmIndex = (pwmIndex + 1) % (sizeof(pwmSteps) / sizeof(int));
        resetPulseCount();        // zera contador sempre na mudanca
    }

    // aplica PWM
    int pwmValue = pwmSteps[pwmIndex];
    setMotorSpeed(pwmValue);

    // leitura do encoder → RPM
    float rpm = getRPM();
    unsigned long t_ms = millis();

    // log no Serial → formato CSV
    Serial.print(t_ms);
    Serial.print(",");
    Serial.print(pwmValue);
    Serial.print(",");
    Serial.println(rpm);

    delay(50); // sampling de log (20 Hz) — nao afeta controle
}
