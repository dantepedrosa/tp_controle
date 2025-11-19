/**
 * @file motor.h
 * @brief Interface para controle do motor via PWM.
 *
 * Este modulo envia sinais de PWM ao motor,
 * controla direcao e gera sinais de teste como degrau.
 *
 * @date 2025-11-18
 * @author Dante
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

/**
 * @brief Configura os pinos do motor (PWM e direcao).
 *
 * Deve ser chamada no setup() antes de controlar o motor.
 */
void setupMotorPins();

/**
 * @brief Ajusta a velocidade do motor via PWM.
 *
 * @param pwmValue Valor entre 0 e 255.
 */
void setMotorSpeed(int pwmValue);

/**
 * @brief Define a direcao de rotacao do motor.
 *
 * @param forward true para frente / false para re.
 */
void setMotorDirection(bool forward);

/**
 * @brief Envia PWM zero e para o motor imediatamente.
 */
void stopMotor();

/**
 * @brief Gera um sinal de entrada tipo degrau (step input).
 *
 * @param amplitude Intensidade do PWM entre 0 e 255.
 */
void sendStepInput(int amplitude);

#endif // MOTOR_H
