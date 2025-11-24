/**
 * @file acquisition_test.ino
 * @brief Coleta de dados para modelagem da funcao de transferencia.
 * 
 * Aplica degraus de PWM e registra (tempo, motor, PWM, RPM) via Serial.
 *
 * @date nov de 2025
 * 
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"
#include "data_logger.h"   // agora usado de verdade!

// Valores de PWM para teste (degraus)
int pwmSteps[] = {80, 120, 160, 200, 240};
int pwmIndex = 0;

// alterna motor A / motor B a cada degrau
bool testingMotorA = true;

unsigned long stepStartTime = 0;
const unsigned long stepDuration = 5000; // 5s por degrau

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando acquisition_test...");
    Serial.println("Salve todos os dados recebidos em ./data/dados_motor.csv");

    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();   // interrupcoes A e B
    setupLogger();              // geração de CSV


}

void loop() {
    // troca de degrau a cada 'stepDuration'
    if (millis() - stepStartTime >= stepDuration) {
        stepStartTime = millis();
        pwmIndex = (pwmIndex + 1) % (sizeof(pwmSteps) / sizeof(int));

        resetPulseCountA();
        resetPulseCountB();
        testingMotorA = !testingMotorA;   // alterna motor testado
    }

    int pwmValue = pwmSteps[pwmIndex];

    if (testingMotorA) {
        setMotorSpeedA(pwmValue);
        setMotorSpeedB(0);
    } else {
        setMotorSpeedB(pwmValue);
        setMotorSpeedA(0);
    }

    // leitura dos encoders
    float rpmA = getRPMA();
    float rpmB = getRPMB();

    // LOG CSV
    // Formato: time_ms, pwmA, rpmA, pwmB, rpmB
    logDualMotor(testingMotorA ? pwmValue : 0,
                 rpmA,
                 testingMotorA ? 0 : pwmValue,
                 rpmB);

    delay(50);  // 20 Hz de log
}