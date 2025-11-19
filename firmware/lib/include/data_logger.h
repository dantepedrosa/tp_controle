/**
 * @file data_logger.h
 * @brief Interface para exportacao de dados via Serial.
 *
 * Este modulo formata e imprime dados experimentais
 * para MATLAB, Python ou Excel.
 *
 * @date 2025-11-18
 * @author Dante
 */

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <Arduino.h>

/**
 * @brief Inicializa a Serial para log.
 *
 * @param baudRate Taxa de transmissao (ex: 115200).
 */
void setupLogger(unsigned long baudRate);

/**
 * @brief Envia tempo e RPM via Serial em formato CSV.
 *
 * @param rpm Valor atual de RPM.
 * @param time_ms Tempo de amostragem em ms.
 */
void logRPM(float rpm, unsigned long time_ms);

/**
 * @brief Log do controlador: referencia, medicao e controle.
 *
 * @param reference Valor desejado.
 * @param measured Valor medido (ex: RPM).
 * @param control Sinal de controle (PWM).
 */
void logControl(float reference, float measured, float control);

/**
 * @brief Imprime cabecalho CSV com nome das colunas.
 */
void printCSVHeader();

/**
 * @brief Envia valores no formato aceito pelo Serial Plotter.
 *
 * @param value1 Primeiro valor a ser exibido.
 * @param value2 Segundo valor a ser exibido.
 */
void plotSerialDebug(float value1, float value2);

#endif // DATA_LOGGER_H
