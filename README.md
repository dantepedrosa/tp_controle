# Projeto: Controle para robô retilíneo (esqueleto)

Arquivos básicos para começar a implementar controle em ESP8266 / Arduino.

Arquitetura:
- `arduino_robot.ino`: sketch principal com loop de controle simples
- `config.h`: pinos e parâmetros físicos (diâmetro da roda, PPR do encoder)
- `Motor.h` / `Motor.cpp`: classe simples para controle via driver L298N
- `Encoder.h` / `Encoder.cpp`: contador de pulsos via interrupção (canal simples)
- `PID.h` / `PID.cpp`: controlador PID simples

Como usar:
1. Abra a pasta `arduino_robot` no Arduino IDE (ou PlatformIO).
2. Ajuste `config.h` com os pinos e parâmetros reais do seu robô (o `config.h` padrão foi ajustado para NodeMCU V3 - ESP8266).
3. Compile e faça upload para o NodeMCU (ESP8266). Use o guia `ESP8266_SETUP.md` para detalhes de configuração do Arduino IDE.

Observação: o sketch usa `Serial.begin(9600)` por padrão (monitor serial a 9600 bps).

Observações importantes:
- O código é um ponto de partida: calibrar `PULSES_PER_REV`, `WHEEL_DIAMETER_M` e os parâmetros do PID.
- Atualmente o `Encoder` usa uma única interrupção (um canal). Para encoders quadratura, substituir por uma implementação de dois canais.
-- `analogWrite` em ESP8266/ESP32 pode precisar de ajustes. Para ESP8266 o projeto já chama `analogWriteRange(255)` em `Motor::begin()`.

# README

Criar arquivo README vazio.
