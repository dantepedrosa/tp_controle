#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

// ====== PINOUT (ajuste conforme sua ligação / NodeMCU V3 - ESP8266) ======
// Observação: os pinos listados abaixo usam números GPIO (por exemplo, D1 = GPIO5).
// Ajuste conforme seu módulo NodeMCU e fiação.

// Motor esquerdo (exemplo)
#define LEFT_PWM 5   // D1
#define LEFT_IN1 14  // D5
#define LEFT_IN2 12  // D6

// Motor direito (exemplo)
#define RIGHT_PWM 4  // D2
#define RIGHT_IN1 13 // D7
#define RIGHT_IN2 15 // D8

// Encoder (pulsos por revolução e pino do encoder de roda)
// Evite usar pinos que possam afetar o boot (GPIO0/GPIO2/GPIO15) para sinais críticos.
#define ENCODER_PIN 2
#define PULSES_PER_REV 20 // ajustar conforme encoder real

// Dimensões da roda (metros)
#define WHEEL_DIAMETER_M 0.065 // ex: 65 mm

// Nota ESP8266:
// - Para ESP8266, recomenda-se configurar a faixa PWM com analogWriteRange(255)
//   na inicialização (feito no Motor::begin()).
// - Alguns pinos influenciam o boot mode; verifique o NodeMCU pinout antes de conectar.

#endif
