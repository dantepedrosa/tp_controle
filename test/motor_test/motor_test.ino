 /**
 * @file motor_test.cpp
 * @brief Teste unitario do MOTOR: resposta a PWM e direcao.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa */

#include <Arduino.h>
#include "config.h"
#include "motor.h"

int pwmValues[] = {80, 120, 160, 200, 255, -200, -160, -120, -80};
int pwmIndex = 0;
unsigned long timerPWM = 0;
const unsigned long stepTime = 3000;  // 3s por valor
bool testingMotorA = true;            // althherna entre motor A e B

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando teste dos MOTORES...");
    setupMotorPins();

    pinMode(PIN_LED_DEBUG, OUTPUT);
    digitalWrite(PIN_LED_DEBUG, HIGH);
    delay(800);
    digitalWrite(PIN_LED_DEBUG, LOW);
}

void loop() {
    if (millis() - timerPWM >= stepTime) {
        timerPWM = millis();
        pwmIndex = (pwmIndex + 1) % (sizeof(pwmValues) / sizeof(int));

        int pwm = pwmValues[pwmIndex];

        // APLICAR PWM NOS DOIS MOTORES AO MESMO TEMPO:
        setMotorSpeedA(pwm);
        setMotorSpeedB(pwm);

        Serial.print("[MOTORES] PWM aplicado = ");
        Serial.println(pwm);
    }
}
