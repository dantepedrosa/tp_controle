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
 * @brief Configura os pinos utilizados pelo encoder.
 *
 * Deve ser chamada apenas uma vez no setup().
 */
void setupEncoderPins();

/**
 * @brief Inicializa a rotina de interrupcao para contagem de pulsos.
 *
 * Deve ser chamada no setup() apos a definicao dos pinos do encoder.
 */
void setupEncoderInterrupt();

/**
 * @brief Calcula e retorna o RPM estimado a partir da contagem de pulsos.
 *
 * @return Valor de RPM como float.
 */
float getRPM();

/**
 * @brief Zera o contador de pulsos do encoder.
 *
 * Usado para iniciar novo ciclo de amostragem.
 */
void resetPulseCount();

/**
 * @brief Aplica um filtro simples (ex: media movel) ao valor de RPM.
 *
 * Opcional. Usado para reduzir ruido da medicao.
 */
void filterRPM();

/**
 * @brief Retorna o numero total de pulsos coletados ate o momento.
 *
 * @return Contagem de pulsos como unsigned long.
 */
unsigned long getPulseCount();

/**
 * @brief Rotina de interrupcao chamada a cada pulso do encoder.
 *
 * Deve ser declarada com IRAM_ATTR para ESP32.
 */
void IRAM_ATTR encoderISR();

#endif // ENCODER_H
