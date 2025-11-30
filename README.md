# Projeto de Controle — Robô 2WD com Encoders

**Modelagem da planta + Controle em malha aberta/fechada + Testes físicos + Documentação automática com Doxygen**

---

## **Estrutura Geral do Projeto**

```
.
├── data
├── docs
├── include
├── lib
├── modelagem
├── src
├── test
├── update_test_libs.sh
└── README.md
```

Cada pasta tem **uma função específica**. A seguir está explicado como usar cada uma.

---

## **data/** — Processamento e análise de dados

Local para **dados experimentais reais** adquiridos com Arduino.

Uso:

* Contém **arquivos CSV** com medições de RPM e PWM.
* Contém **scripts Python** que calculam **função de transferência de 1ª ou 2ª ordem.**
* Contém **gráficos dos resultados reais** de modelagem.

Exemplo:

```
data/
├── dados_motor.csv          ← saída bruta da acquisition_test
├── primeira_ordem.py        ← script para identificar modelo 1ª ordem
├── primeira_ordem/
│   ├── motorA/              ← imagens e resultados de modelo para motor A
│   └── motorB/              ← imagens e resultados de modelo para motor B
```

---

## **docs/** — Documentação técnica

Contém **textos explicativos** e **Doxygen gerado automaticamente**.

| Arquivo/Pasta            | Função                                  |
| ------------------------ | --------------------------------------- |
| DESCRIÇÃO DO PROJETO.md  | Detalha objetivo e teoria inicial       |
| Doxyfile                 | Configurações do Doxygen                |
| doxygen/html/            | Documentação web                        |
| doxygen/latex/refman.pdf | Documentação compilada em PDF           |
| SpeedCtrlMotorBIA.ino    | código de referência (motor + controle) |

---

## **include/** — Headers Globais (.h)

Arquivos usados por **todo o código do robô**:

```
include/
└── config.h      ← pinos, defines e constantes (ex: Ts, PULSES_PER_REV)
```

**Você NÃO altera lógica aqui.**
**Apenas calibra valores conforme o hardware.**

---

## **lib/** — Módulos Reutilizáveis

Código organizado por **funções específicas**:

```
lib/
├── motor/                     ← controle PWM e direção
├── encoder/                   ← leitura de RPM via interrupção
├── controller/                ← lógica de controle em malha fechada
└── data_logger/               ← salva serial em formato CSV
```

Cada módulo tem:

```
nome_modulo/
├── nome_modulo.h   ← protótipos e documentação doxygen
└── nome_modulo.cpp ← implementação REAL
```

---

## **src/** — PROGRAMA FINAL (malha fechada / robô real)

```
src/
└── main.cpp     ← Código principal (malha fechada)
```

Aqui será implementado o **controle real** usando o modelo identificado.

---

## **test/** — Testes físicos separados

Cada pasta pode ser **aberta diretamente no Arduino IDE** e contém **apenas os arquivos necessários** para compilar e rodar o sketch.

```
test/
├── config_test/          ← testa se leitura dos pinos está correta
├── encoder_test/         ← valida encoder + interrupções
├── motor_test/           ← valida PWM e sentido
├── acquisition_test/     ← coleta dados reais para modelagem
├── test_straight_line/   ← malha fechada simples (reta)
└── ...
```

A pasta `test/...` **NÃO usa lib/** diretamente.
Ela é **atualizada automaticamente** via script:

```bash
./update_test_libs.sh    # copia config.h + motor + encoder para cada teste
```

---

## **Fluxo de Desenvolvimento**

| Etapa              | Objetivo                          | Código                   |
| ------------------ | --------------------------------- | ------------------------ |
| 1️⃣ Teste de pinos | Ver se config.h está correto      | `config_test/`           |
| 2️⃣ Motor PWM      | Ver sentido / velocidade          | `motor_test/`            |
| 3️⃣ Encoder        | Testar contagem de pulsos         | `encoder_test/`          |
| 4️⃣ Coleta dados   | Obter RPM x PWM                   | `acquisition_test/`      |
| 5️⃣ Modelagem      | Encontrar função de transferência | `data/primeira_ordem.py` |
| 6️⃣ Retas / curva  | Testar controle simples           | `test_straight_line/`    |
| 7️⃣ FINAL          | Controle em malha fechada         | `src/main.cpp`           |

---

## **Automação do pipeline**

```bash
# coleta dados reais via serial
acquisition_test.ino  ➜  dados_motor.csv

# processa em python
python data/primeira_ordem.py  ➜ modelo identificado

# aplica controle real
src/main.cpp  ➜ malha fechada
```

---

## **Modelagem da planta (Python)**

Exemplo real baseado no CSV:

```python
from control import tf, step_response
# carregar CSV e descobrir K e tau...
G = tf([K], [tau, 1])
```

Gravar gráficos em:

```
data/primeira_ordem/motorA/pwm_150.png
```

---

## **Objetivo final**

**Robô andando reto NA VIDA REAL** usando controle automático utilizando malha fechada e modelo obtido matematicamente.

---
