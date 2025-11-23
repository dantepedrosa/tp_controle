 /**
 * @file motor_test.cpp
 * @brief Teste unitario do MOTOR: resposta a PWM e direcao.
 *
 * @date nov de 2025
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"

int pwmValues[] = {80, 120, 160, 200, 255};
int pwmIndex = 0;
unsigned long timerPWM = 0;
const unsigned long stepTime = 3000;  // 3s por valor

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Iniciando teste do MOTOR PWM...");
    setupMotorPins();


    // REMOVER COM CIRCUITO - Pisca o LED builtin para indicar que o loop esta rodando
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
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

    if (millis() - timerPWM >= stepTime) {
        timerPWM = millis();
        pwmIndex = (pwmIndex + 1) % (sizeof(pwmValues) / sizeof(int));

        int pwm = pwmValues[pwmIndex];
        setMotorSpeed(pwm);

        Serial.print("PWM aplicado = ");
        Serial.println(pwm);
    }
}
