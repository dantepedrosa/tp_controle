# DANTE – Encoder e Modelagem

## 20 de novembro
- [ ] Criar config.h com pinos do ESP32 e definicao de Ts
- [ ] Implementar setupEncoderPins() em encoder.cpp
- [ ] Implementar setupEncoderInterrupt() e encoderISR()
- [ ] Garantir compilacao do encoder sem erros
- [ ] Testar encoder com encoder_test.ino

## 21 de novembro
- [ ] Implementar getRPM() corretamente
- [ ] Implementar resetPulseCount()
- [ ] Iniciar filterRPM() (opcional)
- [ ] Criar acquisition_test.ino chamando motor + encoder
- [ ] Coletar dados reais e salvar em /data/*.csv
- [ ] Entregar dados ao colega B para modelagem

## 22 de novembro
- [ ] Criar script de modelagem (funcao_transferencia.py ou .m)
- [ ] Calcular funcao de transferencia real do motor
- [ ] Validar linearidade e invariancia do sistema (identificacao LIT)
- [ ] Entregar parametros reais ao colega B para o controlador
- [ ] Registrar resultados no relatorio (docs/relatorio.pdf)
- [ ] Participar dos testes integrados do controlador final


# FILIPE – Motor e Controle Digital

## 20 de novembro
- [ ] Implementar setupMotorPins() em motor.cpp
- [ ] Implementar setMotorSpeed(int pwmValue)
- [ ] Criar esqueleto basico de main_controller.ino
- [ ] Garantir compilacao com includes corretos
- [ ] Testar motor com motor_test.ino

## 21 de novembro
- [ ] Implementar sendStepInput() para testes experimentais
- [ ] Implementar setupLogger() e logRPM() em data_logger.cpp
- [ ] Auxiliar na coleta de dados com acquisition_test.ino
- [ ] Criar script de leitura de CSV para plotar sinais
- [ ] Preparar estrutura para modelagem futura (modelagem/*.m)

## 22 de novembro
- [ ] Implementar computeControl() em controller.cpp (PI/PID discreto)
- [ ] Unir encoder + motor + controller em main_controller.ino
- [ ] Testar malha fechada real com o robo
- [ ] Implementar logControl() para salvar dados finais
- [ ] Adicionar resultados experimentais na pasta /docs
- [ ] Finalizar integracao com pessoa A
