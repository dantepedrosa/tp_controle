/**
 * @file data_logger.h
 * @brief Rotinas para salvar dados experimentais via Serial.
 *
 * Permite registrar valores de RPM e PWM dos DOIS motores
 * para analise posterior e modelagem da funcao de transferencia real.
 *
 * @date nov de 2025
 * 
 * @author Dante Junqueira Pedrosa
 * @author Joao Monteiro Delveaux Silva
 * @author Samantha Kelly de Souza Sena
 * @author Felipe Augusto Cruz Sousa
 */

#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

/**
 * @brief Inicializa configuracao de log e imprime cabeçalho CSV.
 */
void setupLogger();

/**
 * @brief Registra os dados dos dois motores.
 *
 * @param pwmA PWM aplicado ao motor A.
 * @param rpmA RPM do motor A.
 * @param pwmB PWM aplicado ao motor B.
 * @param rpmB RPM do motor B.
 */
void logDualMotor(int pwmA, float rpmA, int pwmB, float rpmB);

/**
 * @brief (Opcional) log para controle em malha fechada.
 *
 * @param setA Setpoint de RPM motor A.
 * @param ctrlA Saida do controlador motor A.
 * @param setB Setpoint de RPM motor B.
 * @param ctrlB Saida do controlador motor B.
 */
void logControl(float setA, float ctrlA, float setB, float ctrlB);

#endif // DATA_LOGGER_H
