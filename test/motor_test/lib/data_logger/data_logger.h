/**
 * @file data_logger.h
 * @brief Rotinas para salvar dados experimentais via Serial.
 *
 * Permite registrar valores de RPM, PWM e tempo, para analise posterior
 * e modelagem da funcao de transferencia real dos motores.
 *
 * @date nov de 2025
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

/**
 * @brief Inicializa configuracao de log.
 *
 * Cria cabecalhos e prepara a comunicacao serial.
 */
void setupLogger();

/**
 * @brief Registra um dado de RPM e PWM.
 *
 * @param pwm Valor de PWM aplicado.
 * @param rpm Valor de RPM medido.
 */
void logRPM(int pwm, float rpm);

/**
 * @brief Registra dados adicionais para controle.
 *
 * @param setpoint Valor de referencia de RPM.
 * @param control Saida calculada pelo controlador.
 */
void logControl(int setpoint, float control);

#endif // DATA_LOGGER_H
