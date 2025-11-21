/**
 * @file controller.h
 * @brief Implementacao de controlador PI ou PID discreto.
 *
 * Este modulo calcula a saida de controle com base
 * no erro entre referencia e velocidade medida.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @brief Configura parametros do controlador (Kp, Ki, Kd).
 */
void setupController();

/**
 * @brief Calcula a acao de controle.
 *
 * @param setpoint Valor de RPM desejado.
 * @param measured Valor de RPM medido.
 * @return Saida do controle (ex: PWM).
 */
float computeControl(float setpoint, float measured);

/**
 * @brief Zera estados internos do controlador.
 */
void resetController();

#endif // CONTROLLER_H
