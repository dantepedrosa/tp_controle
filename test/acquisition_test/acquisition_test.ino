/**
 * @file acquisition_test.ino
 * @brief Teste experimental com pausa — AGORA roda motor A e B corretamente.
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// ===== PARAMETROS EXPERIMENTO =====
unsigned long lastT = 0;
unsigned long stepStartTime = 0;

bool testingMotorA = true;        // alterna motor A / B
int pwmSteps[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255};
int pwmIndex = 0;

const unsigned long stepDuration  = 5000;  // motor ligado
const unsigned long pauseDuration = 3000;  // motor parado
bool inPause = false;

bool finished = false;
int motorCount = 0;   // conta quantos motores ja foram testados (max = 2)

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();

    Serial.println("time_ms,motor,pwm,speedA,speedB");

    stepStartTime = millis();
}

void loop() {
    if (finished) return;

    unsigned long now = millis();

    // ---------- PAUSA ENTRE DEGRAUS ----------
    if (inPause) {
        stopMotors();

        if (now - stepStartTime >= pauseDuration) {
            inPause = false;
            stepStartTime = now;

            pwmIndex++;

            if (pwmIndex >= (sizeof(pwmSteps) / sizeof(int))) {
                pwmIndex = 0;
                testingMotorA = !testingMotorA;
                motorCount++;

                if (motorCount >= 2) {              // SO FINALIZA QUANDO MOTOR A E B FOREM TESTADOS
                    Serial.println("=== EXPERIMENTO FINALIZADO ===");
                    finished = true;
                }
            }
        }
        return;
    }

    // ---------- PASSO DE MOTOR ----------
    int pwmValue = pwmSteps[pwmIndex];

    if (testingMotorA) {
        setMotorSpeedA(pwmValue);
        setMotorSpeedB(0);
    } else {
        setMotorSpeedA(0);
        setMotorSpeedB(pwmValue);
    }

    if (now - stepStartTime >= stepDuration) {
        inPause = true;
        stepStartTime = now;
        return;
    }

    // ---------- COLETA: PULSOS / Ts ----------
    if ((now - lastT) >= (Ts * 1000)) {
        lastT = now;

        int speedA = getSpeedA();
        int speedB = getSpeedB();

        Serial.print(now);
        Serial.print(",");
        Serial.print(testingMotorA ? "A" : "B");
        Serial.print(",");
        Serial.print(pwmValue);
        Serial.print(",");
        Serial.print(speedA);
        Serial.print(",");
        Serial.println(speedB);
    }
}
