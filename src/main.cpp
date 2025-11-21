// Placeholder: original firmware/main_controller/main_controller.ino was not provided

#include <Arduino.h>
#include "config.h"

void setup() {
    Serial.begin(DEBUG_SERIAL_BAUD);
    Serial.println("Placa detectada: " BOARD_NAME);
}

void loop() {
    static bool initialized = false;
    if (!initialized) {
        pinMode(LED_BUILTIN, OUTPUT);
        initialized = true;
    }

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}