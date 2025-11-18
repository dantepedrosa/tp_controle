# Atividade Avaliativa Opcional: Construção e Projeto de

# Controle para um Robô de Trajetória Retilínea

### Prof. Fernando Souza

### 21 de outubro de 2025

## Objetivo do Projeto

Construir um robô de 4 rodas dotado de sistema de controle para percorrer 5 metros em linha
reta com precisão. Pode ser construído um robô com tração nas 4 rodas ou em 2 rodas. Cada roda
tracionada deve ser acionada por um motor DC independente com encoder incremental, controlado
por ESP32.
Robô semelhante ao desenvolvido em:
{\https://youtu.be/xH4Z9icRSbw?si=9xRTURmNSm_Mf728}

## Componentes Necessários

- 4x (ou 2x) Motores DC TT
- 4x (ou 2x) encoders (modelo a definir)
- 1x Placa ESP
- 1x Chassi robótico 4WD
- 1x Driver de motores L298N
- Baterias
- Cabos e conectores diversos

## Etapas do Projeto

### 1. Montagem do Robô e Descrição dos Componentes

Entregável: Relatório técnico com:

- Especificações completas dos componentes
- Diagrama elétrico do sistema
- Esquema de montagem mecânica


- Relatório fotográfico da montagem
Especificações a documentar:
- Tensão nominal
- RPM em vazio
- Resolução dos encoders (pulsos/rotação)

### 2. Modelagem Matemática dos Motores

Determinar experimentalmente funções de transferência que representam aproxima-
damente a dinâmica do Motor DC:

- Função de transferência de primeira ordem
- Função de transferência de primeira ordem
Entregável: Relatório com:
- Descrição do processo de obtenção das funções de transferência
- Experimentos para validação do modelo

### 3. Classificação dos motores via experimento

- Linearidade
- Invariânvia no tempo
- Estabilidade

### 4. Projeto do Controlador

1. Controlador Proporcional (P)
2. Controlador Proporcional-Integral (PI)
3. Controlador Proporcional-Integral-Derivativo (PID)
    Controlador a Implementar. Escolher um dos controladores projetados anterior-
mente com justificativa para implementação no robô.
1. Obter equação de diferença que representa o controlador escolhido para implementação.

### 5. Implementação no ESP

1. Código
2. Descrição das aproximações realizadas


### 6. Validação Experimental

Métricas de Desempenho:

- Desvio lateral máximo
- Tempo total de percurso

## Entrega Final

Data de Entrega: [antes da 3ª prova]
Itens a Entregar:

1. Relatório técnico completo (PDF)
2. Código fonte comentado (.ino)
3. Vídeo da demonstração (max. 3 minutos)
4. Apresentação dos resultados (slides)

## Referências Bibliográficas

1. OGATA, K. Engenharia de Controle Moderno. 5ª ed.
2. NISE, N. S. Sistemas de Controle Automático. 7ª ed.
3. Datasheets: Motores TT, ESP
4. Documentação Arduino ESP

## Observações Importantes

- O projeto deve ser realizado em grupos de no máximo 4 alunos
- Todos os membros devem participar de todas atividades
- O código deve ser bem documentado e comentado

### Bom Trabalho!


