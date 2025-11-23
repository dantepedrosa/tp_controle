/**
 * @file config.h
 * @brief Definicoes de pinos e constantes do projeto, com suporte a multiplas placas.
 *
 * Detecta automaticamente se o codigo esta sendo compilado para:
 *  - Arduino Nano
 *  - ESP32
 *  - ESP8266
 *
 * Define os pinos adequados para motor, encoder e LED de debug.
 * Tambem define constantes de controle como Ts.
 * 
 * Utilização em ino:
 * 
 * @code
 * #include "config.h"
 * 
 * void setup() {
 *     Serial.begin(DEBUG_SERIAL_BAUD);
 *     Serial.println("Placa detectada: " BOARD_NAME);
 * }
 * @endcode
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

// ======= TEMPO DE AMOSTRAGEM =======
#define Ts 0.01f     // tempo de amostragem em segundos (10 ms)

// ======= DEBUG OPCIONAL =======
#define DEBUG_SERIAL_BAUD 9600

// ======= ENCODER =======
#ifndef PULSES_PER_REV
#define PULSES_PER_REV 20
#endif

// ======= DETECCAO DA PLACA =======
#if defined(ESP32)
    #define BOARD_NAME "ESP32"

    // Pinos do ESP32
    #define PIN_MOTOR_PWM    23
    #define PIN_MOTOR_DIR    22
    #define PIN_ENCODER_A    34
    #define PIN_ENCODER_B    35
    #define PIN_LED_DEBUG    2

#elif defined(ESP8266)
    #define BOARD_NAME "ESP8266"

    // Pinos do ESP8266 (NodeMCU)
    #define PIN_MOTOR_PWM    D1
    #define PIN_MOTOR_DIR    D2
    #define PIN_ENCODER_A    D5
    #define PIN_ENCODER_B    D6
    #define PIN_LED_DEBUG    D4    // LED onboard

#elif defined(ARDUINO_AVR_NANO)
    #define BOARD_NAME "ARDUINO_NANO"

    // Pinos do Arduino Nano
    #define PIN_MOTOR_PWM    9
    #define PIN_MOTOR_DIR    8
    #define PIN_ENCODER_A    2    // suporte a interrupcao
    #define PIN_ENCODER_B    3
    #define PIN_LED_DEBUG    13   // LED onboard

#else
    #define BOARD_NAME "UNKNOWN"
    #warning Nao foi possivel detectar a placa. Definindo pinos genericos:

    #define PIN_MOTOR_PWM    9
    #define PIN_MOTOR_DIR    8
    #define PIN_ENCODER_A    2
    #define PIN_ENCODER_B    3
    #define PIN_LED_DEBUG    13
#endif

#endif // CONFIG_H