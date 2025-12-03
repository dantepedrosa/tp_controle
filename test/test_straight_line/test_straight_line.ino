/**
 * @file test_straight_line.ino
 * @brief Controle para andar em linha reta usando modelos identificados de 1a ordem.
 *
 *   1. Determina PWM base desejado (ex: 200)
 *   2. Usa modelo A e B para prever ganho K_A e K_B
 *   3. Aplica PWM_A_ff e PWM_B_ff que igualam velocidades
 *   4. PI regula apenas o erro residual = rpmA - rpmB
 */

#include <Arduino.h>
#include "config.h"
#include "motor.h"
#include "encoder.h"

// ------------------------------------------------------------
//  TABELAS DOS MODELOS IDENTIFICADOS
// ------------------------------------------------------------
typedef struct {
    int pwm;      // PWM aplicado
    float K;      // ganho estatico (velocidade por PWM)
    float T;      // constante de tempo (não usada neste controle)
} MotorModel;

// Tabela de pontos do modelo identificado do motor B, formato {pwm, K, T}.
MotorModel modelA[] = {
    {120, 0.000, 0.500}, {130, 1.256, 0.000}, {140, 1.167, 0.190},
    {150, 1.207, 0.181}, {160, 1.247, 0.163}, {170, 1.302, 0.159},
    {180, 1.358, 0.146}, {190, 1.425, 0.129}, {200, 1.424, 0.152},
    {210, 1.473, 0.145}, {220, 1.497, 0.141}, {230, 1.578, 0.146},
    {240, 1.539, 0.113}, {250, 1.558, 0.126}, {255, 1.696, 0.112}
};

// Tabela de pontos do modelo identificado do motor B, formato {pwm, K, T}.
MotorModel modelB[] = {
    {130, 0.000, 0.500}, {140, 1.353, 0.136}, {150, 1.562, 0.182},
    {160, 1.612, 0.196}, {170, 1.559, 0.142}, {180, 1.673, 0.115},
    {190, 1.759, 0.174}, {200, 1.740, 0.157}, {210, 1.795, 0.137},
    {220, 1.880, 0.152}, {230, 1.856, 0.151}, {240, 1.890, 0.131},
    {250, 1.825, 0.125}, {255, 1.887, 0.117}
};

int modelA_size = sizeof(modelA) / sizeof(MotorModel);
int modelB_size = sizeof(modelB) / sizeof(MotorModel);

// FUNÇÃO DE INTERPOLAÇÃO LINEAR DO GANHO K(PWM)
// Busca na tabela o modelo a partir do PWM e retorna o cálculo
float interpK(const MotorModel *table, int N, int pwm)
{
    if (pwm <= table[0].pwm)
        return table[0].K;

    if (pwm >= table[N - 1].pwm)
        return table[N - 1].K;

    for (int i = 0; i < N - 1; i++) {
        if (pwm >= table[i].pwm && pwm <= table[i + 1].pwm) {

            float pwm0 = table[i].pwm;
            float pwm1 = table[i + 1].pwm;
            float K0   = table[i].K;
            float K1   = table[i + 1].K;

            float alpha = (pwm - pwm0) / (pwm1 - pwm0);
            return K0 + alpha * (K1 - K0);
        }
    }
    return table[N - 1].K;
}

// ------------------------------------------------------------
//                 PARÂMETROS DO CONTROLE
// ------------------------------------------------------------
const int PWM_BASE = 200;
const float Ts_ms = Ts * 1000.0;

// PI diferencial (erro = rpmA - rpmB)
float Kp = 2.0;
float Ki = 20.0;

float e_prev = 0;
float corr = 0;

unsigned long lastT = 0;



void setup()
{
    Serial.begin(DEBUG_SERIAL_BAUD);

    setupMotorPins();
    setupEncoderPins();
    setupEncoderInterrupts();

    Serial.println("time_ms,rpmA,rpmB,PWM_A,PWM_B,corr");
}

void loop()
{
    unsigned long now = millis();
    if (now - lastT < Ts_ms) return;
    lastT = now;

    // leitura de pulsos
    int pA = getSpeedA();
    int pB = getSpeedB();

    float rpmA = (float)pA * (60.0 / Ts) / PULSES_PER_REV;
    float rpmB = (float)pB * (60.0 / Ts) / PULSES_PER_REV;

    // feedforward baseado no ganho K(PWM)
    float KA = interpK(modelA, modelA_size, PWM_BASE);
    float KB = interpK(modelB, modelB_size, PWM_BASE);

    float PWM_A_ff = PWM_BASE * (KB / KA);
    float PWM_B_ff = PWM_BASE * (KA / KB);

    // erro diferencial
    float e = rpmA - rpmB;

    // controlador PI
    corr += Kp * (e - e_prev) + Ki * Ts * e;
    e_prev = e;

    // limite da correcao
    if (corr > 80) corr = 80;
    if (corr < -80) corr = -80;

    // PWM final
    int pwmA = PWM_A_ff - corr;
    int pwmB = PWM_B_ff + corr;

    // saturação para faixa 0–255
    if (pwmA < 0) pwmA = 0;
    if (pwmA > 255) pwmA = 255;

    if (pwmB < 0) pwmB = 0;
    if (pwmB > 255) pwmB = 255;

    // aplica PWM corrigido
    setMotorSpeedA(pwmA);
    setMotorSpeedB(pwmB);

    Serial.print(now); Serial.print(",");
    Serial.print(rpmA); Serial.print(",");
    Serial.print(rpmB); Serial.print(",");
    Serial.print(pwmA); Serial.print(",");
    Serial.print(pwmB); Serial.print(",");
    Serial.println(corr);
}
