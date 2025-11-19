/**
 * @file controller.h
 * @brief Interface para o controlador digital PI/PID.
 *
 * Implementa o controlador discreto em tempo real
 * usando equacao de diferenca para gerar o sinal de controle.
 *
 * @date 2025-11-18
 * @author Dante
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

// ---------- VARIAVEIS GLOBAIS ----------
extern float kp, ki, kd;        ///< Ganhos do controlador
extern float Ts;                ///< Tempo de amostragem em segundos
extern float e_k, e_k1, e_k2;   ///< Erros do sistema
extern float u_k, u_k1, u_k2;   ///< Controles gerados

/**
 * @brief Configura os parametros do controlador digital.
 *
 * @param Kp Ganho proporcional.
 * @param Ki Ganho integral.
 * @param Kd Ganho derivativo.
 * @param Ts_sec Tempo de amostragem.
 */
void setupController(float Kp, float Ki, float Kd, float Ts_sec);

/**
 * @brief Calcula o proximo valor de controle usando equacao de diferenca.
 *
 * @param reference Valor desejado (setpoint).
 * @param measured_value Valor medido (ex: RPM).
 * @return Sinal de controle calculado (para PWM).
 */
float computeControl(float reference, float measured_value);

/**
 * @brief Zera variaveis internas do controlador.
 *
 * Deve ser usada quando o controle for reiniciado.
 */
void resetController();

#endif // CONTROLLER_H
