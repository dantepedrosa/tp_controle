# Plano de Trabalho (18/11 — 22/11)

Objetivo: organizar tarefas para dois desenvolvedores (Dev A e Dev B) começar do zero no projeto "Controle para robô de trajetória retilínea" e entregar um esqueleto funcional, relatórios e materiais para validação experimental até 22/11.

Instruções gerais
- O prazo proposto começa hoje: **18/11** e termina **22/11**.
- Cada tarefa tem um responsável sugerido (Dev A / Dev B) — isso pode ser trocado entre os desenvolvedores.
- Marcar a tarefa como "done" no repositório (issue/PR) quando entregue. Incluir testes básicos, fotos ou logs conforme aplicável.

Resumo de papéis sugeridos
- Dev A: Hardware, eletrônica, montagem, testes de sensores
- Dev B: Software, modelagem, controlador e integração

Cronograma e tarefas (ordem cronológica)

Dia 1 — 18/11 (kickoff e preparação)

- Tarefa 1: Reunião de kickoff (30–60 min)
  - Responsável sugerido: ambos
  - Saída: lista final de componentes, divisão de tarefas, confirmação de datas
  - Critério de aceitação: documento curto (1 página) com itens e responsabilidades

- Tarefa 2: Inventário de componentes e diagrama elétrico inicial
  - Responsável sugerido: Dev A
  - Prazo: 18/11 (final do dia)
  - Saída: fotos dos componentes, planilha com tensões, RPM nominal, PPR dos encoders, e um diagrama de ligação (PDF/PNG)

- Tarefa 3: Criar repositório/estrutura de pastas e README inicial
  - Responsável sugerido: Dev B
  - Prazo: 18/11 (final do dia)
  - Saída: `README.md`, `doc/`, `src/`, `include/`, `tests/` com instruções de compilação

Dia 2 — 19/11 (montagem e testes básicos)

- Tarefa 4: Montagem mecânica e montagem elétrica básica
  - Responsável sugerido: Dev A
  - Prazo: 19/11 (final do dia)
  - Saída: robô fisicamente montado, fotos, observações de ajustes necessários

- Tarefa 5: Sketch de teste de hardware (PWM e leitura de encoder simples)
  - Responsável sugerido: Dev B
  - Prazo: 19/11 (final do dia)
  - Saída: sketch que varre PWM e conta pulsos do encoder; log serial a 9600bps

Dia 3 — 20/11 (identificação e modelagem)

- Tarefa 6: Experimento para identificação da dinâmica do motor (resposta a degrau)
  - Responsável sugerido: Dev A (execução) + Dev B (registro/formatação dos dados)
  - Prazo: 20/11 (final do dia)
  - Saída: dados do degrau (CSV), gráfico de velocidade vs tempo, estimativa de TF de 1ª ordem

- Tarefa 7: Implementar classe Motor, Encoder e PID (esqueleto)
  - Responsável sugerido: Dev B
  - Prazo: 20/11 (final do dia)
  - Saída: código inicial em `src/` e `include/` (APIs documentadas)

Dia 4 — 21/11 (projeto do controlador e integração)

- Tarefa 8: Projetar controladores (P, PI, PID) e escolher candidato final
  - Responsável sugerido: Dev B
  - Prazo: 21/11 (meio do dia)
  - Saída: documento curto com parâmetros propostos, justificativa e equação de diferença para implementação

- Tarefa 9: Integrar controlador no sketch e testar percurso curto (1 m)
  - Responsável sugerido: ambos (Dev B integra, Dev A testa no robô)
  - Prazo: 21/11 (final do dia)
  - Saída: vídeo curto ou logs mostrando comportamento no percurso curto; ajustar ganhos se necessário

Dia 5 — 22/11 (validação e entrega parcial)

- Tarefa 10: Teste final — percurso de 5 m e coleta de métricas
  - Responsável sugerido: Dev A (execução) + Dev B (coleta e análise de dados)
  - Prazo: 22/11 (meio do dia)
  - Métricas: desvio lateral máximo, tempo total do percurso, overshoot, erro final

- Tarefa 11: Relatório técnico e códigos comentados (entregável parcial)
  - Responsável sugerido: Dev B (código) / Dev A (fotos e medições)
  - Prazo: 22/11 (final do dia)
  - Saída: PDF curto com métodos, resultados e anexos; código `.ino` comentado e pronto para teste

Critérios de priorização e notas
- Priorize estabilidade do robô e segurança ao testar (velocidade baixa). Evitar usar pinos que afetam boot no NodeMCU.
- Se a identificação do motor demorar mais que o previsto, simplifique: use uma aproximação inicial (prim. ordem) e ajuste empiricamente os ganhos do PID.
- Comunicação: mantenha um canal (GitHub issues / Slack / WhatsApp) para perguntas rápidas.

Divisão alternativa (se quiser dividir por módulos)
- Dev A: Hardware, montagem, testes físicos e coleta de dados
- Dev B: Software, modelagem, PID e integração

Checklist de entrega (22/11)
- [ ] Código fonte comentado e compilável para NodeMCU (baud 9600)
- [ ] CSV com dados de identificação e gráficos
- [ ] Vídeo curto demonstrando percurso (máx. 3 min)
- [ ] Relatório técnico em PDF (métodos + resultados)

Contato e notas finais
- Se houver restrições de tempo/hardware, replanejar prioridades com base em: 1) obter dados do encoder, 2) controle simples de distância, 3) controle diferencial para manter a reta.

Boa sorte — se quiser, eu posso gerar templates para o relatório (LaTeX/Markdown), sketches de teste (PWM/encoder) e um script para análise de dados (Python) para acelerar o trabalho.
