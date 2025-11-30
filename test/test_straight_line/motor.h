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
 * @brief Configura os pinos utilizados pelos motores.
 *
 * Deve ser chamada uma vez no setup().
 */
void setupMotorPins();

/**
 * @brief Define a velocidade do Motor A (esquerdo).
 *
 * @param pwmValue Valor entre -255 e 255 (PWM e direcao).
 */
void setMotorSpeedA(int pwmValue);

/**
 * @brief Define a velocidade do Motor B (direito).
 *
 * @param pwmValue Valor entre -255 e 255 (PWM e direcao).
 */
void setMotorSpeedB(int pwmValue);

/**
 * @brief Envia o mesmo degrau de PWM para ambos os motores.
 *
 * Usado para testes em malha aberta.
 *
 * @param pwmValue Valor entre 0 e 255.
 */
void sendStepInput(int pwmValue);

/**
 * @brief Para ambos os motores imediatamente.
 *
 * Define PWM = 0 para os dois motores.
 */
void stopMotors();

#endif // MOTOR_H
