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
#define PULSES_PER_REV 20        // definir real conforme data sheet do encoder
#endif

// ======= DETECCAO DA PLACA E DEFINIÇÃO DE PINOS =========
#if defined(ESP32)
    #define BOARD_NAME "ESP32"

    // MOTOR A - L298N
    #define PIN_MOTOR_A_EN    23
    #define PIN_MOTOR_A_IN1   22
    #define PIN_MOTOR_A_IN2   21

    // MOTOR B - L298N
    #define PIN_MOTOR_B_EN    19
    #define PIN_MOTOR_B_IN1   18
    #define PIN_MOTOR_B_IN2   5

    // ENCODER A
    #define PIN_ENCODER_A_A   34
    #define PIN_ENCODER_B_A   35

    // ENCODER B
    #define PIN_ENCODER_A_B   32
    #define PIN_ENCODER_B_B   33

    #define PIN_LED_DEBUG     2

#elif defined(ESP8266)
    #define BOARD_NAME "ESP8266"

    // MOTOR A - L298N
    #define PIN_MOTOR_A_EN    D1
    #define PIN_MOTOR_A_IN1   D2
    #define PIN_MOTOR_A_IN2   D3

    // MOTOR B - L298N
    #define PIN_MOTOR_B_EN    D8
    #define PIN_MOTOR_B_IN1   D7
    #define PIN_MOTOR_B_IN2   D6

    // ENCODER A
    #define PIN_ENCODER_A_A   D5
    #define PIN_ENCODER_B_A   D4

    // ENCODER B
    #define PIN_ENCODER_A_B   D0
    #define PIN_ENCODER_B_B   D1

    #define PIN_LED_DEBUG     D2

#elif defined(ARDUINO_AVR_NANO)
    #define BOARD_NAME "ARDUINO_NANO"

    // MOTOR A - L298N
    #define PIN_MOTOR_A_EN    9
    #define PIN_MOTOR_A_IN1   8
    #define PIN_MOTOR_A_IN2   7

    // MOTOR B - L298N
    #define PIN_MOTOR_B_EN    6
    #define PIN_MOTOR_B_IN1   5
    #define PIN_MOTOR_B_IN2   4

    // ENCODER A
    #define PIN_ENCODER_A_A   2        // interrupcao INT0
    #define PIN_ENCODER_B_A   3        // interrupcao INT1

    // ENCODER B
    #define PIN_ENCODER_A_B   A0
    #define PIN_ENCODER_B_B   A1

    #define PIN_LED_DEBUG     13

#else
    #define BOARD_NAME "UNKNOWN"
    #warning Nao foi possivel detectar a placa. Definindo pinos genericos:

    // MOTOR A - L298N
    #define PIN_MOTOR_A_EN    9
    #define PIN_MOTOR_A_IN1   8
    #define PIN_MOTOR_A_IN2   7

    // MOTOR B - L298N
    #define PIN_MOTOR_B_EN    6
    #define PIN_MOTOR_B_IN1   5
    #define PIN_MOTOR_B_IN2   4

    // ENCODER A
    #define PIN_ENCODER_A_A   2
    #define PIN_ENCODER_B_A   3

    // ENCODER B
    #define PIN_ENCODER_A_B   A0
    #define PIN_ENCODER_B_B   A1

    #define PIN_LED_DEBUG     13
#endif

#endif // CONFIG_H
