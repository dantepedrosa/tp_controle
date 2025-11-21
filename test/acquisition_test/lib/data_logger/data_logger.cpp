/**
 * Minimal data_logger implementation (original source not provided in input).
 * Writes CSV-like lines to Serial for acquisition and control logging.
 */

#include <Arduino.h>
#include "data_logger.h"
#include "config.h"

void setupLogger() {
    Serial.println("time_ms,pwm,rpm");
}

void logRPM(int pwm, float rpm) {
    unsigned long t = millis();
    Serial.print(t);
    Serial.print(",");
    Serial.print(pwm);
    Serial.print(",");
    Serial.println(rpm);
}

void logControl(int setpoint, float control) {
    unsigned long t = millis();
    Serial.print(t);
    Serial.print(",");
    Serial.print(setpoint);
    Serial.print(",");
    Serial.println(control);
}
