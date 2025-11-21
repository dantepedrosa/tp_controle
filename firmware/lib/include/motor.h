/**
 * @file motor.h
 * @brief Interface de controle dos motores DC por PWM.
 *
 * Este modulo permite configurar os pinos de acionamento do motor,
 * controlar velocidade via PWM e definir direcao de rotacao.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#ifndef MOTOR_H
#define MOTOR_H

/**
 * @brief Configura os pinos utilizados para o controle do motor.
 *
 * Deve ser chamada apenas uma vez no setup().
 */
void setupMotorPins();

/**
 * @brief Define a velocidade e direcao do motor.
 *
 * @param pwmValue Valor entre -255 e 255 (sinal define direcao).
 */
void setMotorSpeed(int pwmValue);

/**
 * @brief Envia um degrau de PWM para testar resposta em malha aberta.
 *
 * @param pwmValue Valor entre 0 e 255.
 */
void sendStepInput(int pwmValue);

#endif // MOTOR_H
