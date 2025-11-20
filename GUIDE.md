# Lógica Geral do Desenvolvimento do Projeto 4WD Robô de Controle

Este documento descreve a ordem ideal de desenvolvimento, o fluxo lógico das tarefas, e o que deve ser verificado em cada etapa para garantir que o projeto funcione corretamente e seja concluído sem retrabalho.

---

## 1. Etapa de Preparação (base do sistema)
**Objetivo**: garantir que todo o firmware está organizado e compila.

**Ações necessárias:**
- Criar estrutura de pastas e arquivos (.ino, .h, .cpp)
- Definir `config.h` com pinos e constantes
- Dividir responsabilidades entre pessoas
- Garantir que encoder e motor testam de forma INDIVIDUAL

**Não avançar para controle sem:**
- Encoder medindo RPM corretamente
- Motor respondendo a PWM com estabilidade
- Código compilando sem erros

---

## 2. Desenvolvimento dos módulos (C/C++ com .h e .cpp)
**Objetivo**: implementar os módulos de forma modular e independente.

**Ordem ideal de desenvolvimento:**
1. `motor.cpp` e `motor.h` — funções básicas de PWM e direção
2. `encoder.cpp` e `encoder.h` — ISR, contagem de pulsos e RPM
3. `data_logger.cpp` e `data_logger.h` — exportação de dados via Serial
4. `controller.cpp` e `controller.h` — fica por último (depende da modelagem)

**Cada módulo deve passar por teste de unidade (.ino dedicado):**
- `encoder_test.ino` → valida apenas encoder
- `motor_test.ino` → valida apenas motor
- `acquisition_test.ino` → integra encoder + motor + logger
- `main_controller.ino` → versão final com controle REAL

---

## 3. Coleta de Dados e Testes Físicos (dia 21)
**Objetivo**: obter dados REAIS do sistema físico para modelagem.  
Esses dados são muito importantes. O controle depende disso.

**O que deve ser feito:**
- Acionar o motor com degraus de PWM → ex: 80 / 120 / 160 / 200
- Medir RPM via encoder e exportar usando `data_logger.cpp`
- Salvar os dados em `/data/*.csv`
- Plotar os dados com Python ou MATLAB
- Obter graficos de RPM x tempo

**Importante:**  
Sem esses dados, o controlador NÃO PODE ser projetado corretamente.

---

## 4. Modelagem Matemática do Sistema (dia 22 início)
**Objetivo**: extrair a função de transferência REAL do motor.

**Passos recomendados:**
- Carregar os CSV no MATLAB ou Python
- Usar resposta ao degrau para identificar:
  - Ganho K
  - Constante de tempo tau
  - Offset estático (se houver)
- Estimar função de transferência de 1ª ordem:

  $G(s) = K / (tau*s + 1)$

- Verificar:
  - Linearidade (variação de amplitude do degrau)
  - Invariância no tempo (mesmo degrau em tempos diferentes)
  - Estabilidade (resposta converge?)

**Resultado necessário:**
- Função de transferência REAL
- Gráficos salvos na pasta `docs/diagramas`
- Conclusão sobre o comportamento do motor

---

## 5. Projeto do Controlador (PI ou PID)
**Objetivo**: converter a função de transferência em um controlador digital.

**Passos:**
1. Definir tipo de controlador (P, PI ou PID)
2. Obter ganhos contínuos (método empírico / tentativas / Ziegler-Nichols)
3. Discretizar o controlador usando `Ts` definido anteriormente
4. Escrever equação de diferença:

   Exemplo PI discreto:
$u[k] = u[k-1] + kp * (e[k] - e[k-1]) + ki * Ts * e[k]$

**Resultado:**  
Implementar `computeControl()` em `controller.cpp` com fórmula FINAL.

---

## 6. Testes de Controle em Malha Fechada (dia 22 final)
**Objetivo:** validar o controlador com o robô real.

**O que deve acontecer:**
- Controlador calcula PWM automaticamente
- Robô deve atingir **velocidade alvo**
- Observar efeitos de erro, overshoot e estabilidade
- Registrar dados com `logControl()` para análise final

**Se tiver oscilação forte:**
- Reduzir kp
- Aumentar damping (pi ou filtro)
- Verificar saturação de PWM

---

## 7. Fechamento de projeto e relatório
**Itens obrigatórios para entrega:**
- Codigo comentado e estruturado (firmware/)
- Dados experimentais (data/*.csv)
- Modelagem com gráficos (modelagem/*.m ou .py)
- Resultados do controle (docs/*)
- Vídeo de demonstração
- Slides de apresentação
- Relatório completo

**Informações importantes para o relatório:**
- Como cada módulo foi testado
- Justificativa do controlador escolhido
- Comparação entre malha aberta e fechada
- Erros observados e lições aprendidas

---

# Checklist de Conclusão (marcar antes de entregar)

- [ ] Encoder funcionando e com RPM confiavel  
- [ ] Motor controlado corretamente via PWM  
- [ ] Dados experimentais salvos na pasta /data  
- [ ] Funcao de transferencia modelada  
- [ ] Controlador digital implementado (computeControl)  
- [ ] Sistema em malha fechada testado fisicamente  
- [ ] Realimentacao funcionando  
- [ ] Relatorio completo com graficos e analises  
- [ ] Codigo final comentado  
- [ ] Video gravado para apresentacao  
- [ ] Slides prontos  

---
---

# Observacoes Gerais

- O projeto so avanca se **motor+encoder estiverem funcionando**.
- Contador de pulsos deve ser `volatile` e estar dentro de `IRAM_ATTR`.
- Ts deve ser determinado ANTES da modelagem.
- Nao escrever controlador baseado em estimativas teoricas → usar dados reais.
- Evitar reescrever codigo. Modulos devem ser independentes.
- Relatorio deve mostrar **malha aberta X malha fechada**.
- Ao testar PID, usar valores pequenos de kd para evitar oscilacoes.

---
---


# Cronograma

## Pessoa A – Encoder e Modelagem

### 20 de novembro
- [ ] Criar config.h com pinos do ESP32 e definicao de Ts
      (arquivo: firmware/config.h)

- [ ] Implementar setupEncoderPins()
      (arquivo: firmware/lib/src/encoder.cpp, prototipo em encoder.h)

- [ ] Implementar setupEncoderInterrupt() e encoderISR()
      (arquivo: firmware/lib/src/encoder.cpp, prototipos em encoder.h)

- [ ] Garantir compilacao do encoder sem erros
      (afetando encoder.cpp, encoder.h e config.h)

- [ ] Testar encoder usando encoder_test.ino
      (arquivo: firmware/encoder_module/encoder_test.ino)


### 21 de novembro
- [ ] Implementar getRPM() corretamente
      (arquivo: firmware/lib/src/encoder.cpp)

- [ ] Implementar resetPulseCount()
      (arquivo: firmware/lib/src/encoder.cpp)

- [ ] Implementar filterRPM() (opcional, media movel simples)
      (arquivo: firmware/lib/src/encoder.cpp)

- [ ] Criar acquisition_test.ino chamando motor + encoder + logger
      (arquivo: firmware/acquisition_test/acquisition_test.ino)

- [ ] Coletar dados reais e salvar em /data/*.csv
      (saida via Serial, salvar no PC)

- [ ] Entregar dados reais ao colega B para modelagem
      (pasta: data/*.csv)


### 22 de novembro
- [ ] Implementar script de modelagem (funcao_transferencia.py ou .m)
      (arquivo: modelagem/funcao_transferencia.py ou funcao_transferencia.m)

- [ ] Calcular funcao de transferencia real do motor
      (arquivo: modelagem/funcao_transferencia.py ou .m)

- [ ] Validar linearidade e invariancia do sistema (identificacao LIT)
      (arquivo: modelagem/identificacao_lit.m)

- [ ] Entregar parametros reais ao colega B para controlador (ganhos e modelo)
      (comunicacao interna)

- [ ] Registrar resultados no relatorio (dados, graficos, funcao de transferencia)
      (arquivo: docs/relatorio.pdf)

- [ ] Participar dos testes integrados do controlador final
      (arquivo principal: main_controller.ino)


## Pessoa B – Motor e Controle Digital

### 20 de novembro
- [ ] Implementar setupMotorPins()
      (arquivo: firmware/lib/src/motor.cpp, prototipo em motor.h)

- [ ] Implementar setMotorSpeed(int pwmValue)
      (arquivo: firmware/lib/src/motor.cpp)

- [ ] Criar esqueleto basico de main_controller.ino
      (arquivo: firmware/main_controller/main_controller.ino)
      incluir:
         #include "encoder.h"
         #include "motor.h"
         #include "controller.h"
         #include "data_logger.h"
         #include "config.h"

- [ ] Garantir compilacao com includes corretos
      (testar no Arduino IDE ou PlatformIO)

- [ ] Testar motor com motor_test.ino
      (arquivo: firmware/motor_pwm_test/motor_test.ino)


### 21 de novembro
- [ ] Implementar sendStepInput(int amplitude)
      (arquivo: firmware/lib/src/motor.cpp)

- [ ] Implementar setupLogger() e logRPM()
      (arquivo: firmware/lib/src/data_logger.cpp)

- [ ] Auxiliar na coleta com acquisition_test.ino
      (arquivo: firmware/acquisition_test/acquisition_test.ino)

- [ ] Criar script python simples para plotar CSV
      (arquivo: modelagem/funcao_transferencia.py)

- [ ] Preparar estrutura para modelagem futura
      (arquivos em modelagem/*.m e modelagem/*.py)


### 22 de novembro
- [ ] Implementar computeControl() (PI/PID discreto)
      (arquivo: firmware/lib/src/controller.cpp)

- [ ] Unir encoder + motor + controller em main_controller.ino
      (arquivo: firmware/main_controller/main_controller.ino)

- [ ] Criar loop de controle (ex: timer ou millis())
      (arquivo: firmware/main_controller/main_controller.ino)

- [ ] Implementar logControl() para salvar dados finais
      (arquivo: firmware/lib/src/data_logger.cpp)

- [ ] Testar malha fechada real com o robo
      (arquivo principal: main_controller.ino)

- [ ] Adicionar resultados experimentais em docs/
      (pasta: docs/diagramas/ e docs/relatorio.pdf)

- [ ] Finalizar integracao com pessoa A
      (comunicacao + testes finais)

