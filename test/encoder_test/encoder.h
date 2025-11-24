/**
 * @file encoder.h
 * @brief Interface para leitura do encoder e calculo de RPM.
 *
 * Este modulo gerencia a leitura do encoder incremental,
 * usando interrupcoes e contagem de pulsos para calcular
 * a velocidade angular (RPM) do motor.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

/**
 * @brief Configura os pinos dos encoders A e B.
 *
 * Deve ser chamada uma vez no setup().
 */
void setupEncoderPins();

/**
 * @brief Ativa as interrupcoes para ambos os encoders.
 *
 * Deve ser chamada apos setupEncoderPins().
 */
void setupEncoderInterrupts();

/**
 * @brief Retorna o RPM estimado do Motor A.
 *
 * @return RPM do motor A.
 */
float getRPMA();

/**
 * @brief Retorna o RPM estimado do Motor B.
 *
 * @return RPM do motor B.
 */
float getRPMB();

/**
 * @brief Retorna a contagem total de pulsos do encoder A.
 *
 * @return Pulsos acumulados.
 */
unsigned long getPulseCountA();

/**
 * @brief Retorna a contagem total de pulsos do encoder B.
 *
 * @return Pulsos acumulados.
 */
unsigned long getPulseCountB();

/**
 * @brief Zera a contagem de pulsos do encoder A.
 */
void resetPulseCountA();

/**
 * @brief Zera a contagem de pulsos do encoder B.
 */
void resetPulseCountB();

/**
 * @brief ISR (interrupcao) chamada a cada pulso do encoder A.
 */
void IRAM_ATTR encoderISRA();

/**
 * @brief ISR (interrupcao) chamada a cada pulso do encoder B.
 */
void IRAM_ATTR encoderISRB();

#endif // ENCODER_H