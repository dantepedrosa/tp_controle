/**
* @file data_logger.cpp
* @brief Funcoes para facilitar log de dados via Serial.
*
* @date nov de 2025
* 
* @author Dante Junqueira Pedrosa
* @author Joao Monteiro Delveaux Silva
* @author Samantha Kelly de Souza Sena
* @author Felipe Augusto Cruz Sousa
 */

#include <Arduino.h>
#include "data_logger.h"
#include "config.h"

void setupLogger() {
    Serial.println("time_ms,pwmA,rpmA,pwmB,rpmB");
}

void logDualMotor(int pwmA, float rpmA, int pwmB, float rpmB) {
    unsigned long t = millis();
    Serial.print(t);
    Serial.print(",");
    Serial.print(pwmA);
    Serial.print(",");
    Serial.print(rpmA);
    Serial.print(",");
    Serial.print(pwmB);
    Serial.print(",");
    Serial.println(rpmB);
}

void logControl(float setA, float ctrlA, float setB, float ctrlB) {
    unsigned long t = millis();
    Serial.print(t);
    Serial.print(",");
    Serial.print(setA);
    Serial.print(",");
    Serial.print(ctrlA);
    Serial.print(",");
    Serial.print(setB);
    Serial.print(",");
    Serial.println(ctrlB);
}
