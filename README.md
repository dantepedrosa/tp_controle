# tp_controle — Guia de desenvolvimento e como codar

Resumo
- Repositório do trabalho final de controle: código embarcado, testes Arduino, dados experimentais e documentação.
- Este documento descreve onde codar, convenções de código, como testar, e o passo obrigatório de atualizar as "test libs" antes de commits.

Como codar — regras práticas
- Arquivos de produção:
  - lib/: bibliotecas do projeto (módulos reutilizáveis). Cada módulo deve ter header (.h) com comentários Doxygen e implementação (.cpp) clara.
  - src/ (ou pasta principal onde houver sketches): código do sistema/firmware principal.
  - test/: sketches/ projetos prontos para abrir no Arduino IDE / PlatformIO; cada pasta deve conter um README local que descreva hardware necessário e procedimento de teste.
- Convenções de estilo:
  - Comentários públicos com Doxygen (funções, structs, macros importantes).
  - Funções curtas e coesas; modularize lógica complexa em arquivos separados.
  - Nomes: snake_case para variáveis/funcs do C/C++; PascalCase para classes.
  - Indentação: 4 espaços; evite tabs mistos.
  - Header guards em .h: USE #pragma once ou o par tradicional (#ifndef/#define/#endif).
- Boas práticas de alterações:
  - Faça mudanças pequenas e testáveis por PR.
  - Adicione/atualize testes em test/ correspondentes às mudanças.
  - Atualize docs/ quando alterar comportamento ou API pública.

Estrutura de pastas (detalhada)
- data/
  - Propósito: armazenar e processar dados experimentais e gerar gráficos.
  - Sugestão:
    - data/raw/        — dados brutos (não editar).
    - data/processed/  — dados formatados para análise.
    - data/scripts/    — scripts de processamento (Python/Octave/Matlab/R).
    - data/results/    — resultados numéricos (CSV, JSON).
    - data/figures/    — imagens/plots finais.
  - Regra: versione scripts e resultados pequenos; grandes datasets em LFS ou ignore.
- docs/
  - Documentação variada: especificações, relatórios, notas de projeto, diagramas elétricos e mecânicos.
  - Cada documento com metadados (autor, data, versão).
- lib/
  - Implementações modulares (encoder, motor, utils, etc). Exponha APIs em headers.
- src/ ou pasta de sketches
  - Código principal e integração dos módulos.
- test/
  - Sketches e projetos prontos para testes em hardware.
  - Cada subpasta deve compilar por si só; inclua README de teste com instruções de hardware e passos de medição.
- tools/, scripts/, ci/
  - Scripts utilitários: build, atualização de libs, integração contínua.

Como rodar/compilar localmente
- Arduino IDE: abrir a pasta do sketch em test/<nome>.
- Arduino CLI (exemplos):
  - Instalar dependências: arduino-cli core update-index
  - Compilar: arduino-cli compile --fqbn <board_fqbn> path/to/sketch
  - Upload: arduino-cli upload -p <porta> --fqbn <board_fqbn> path/to/sketch
- PlatformIO: abrir projeto no VSCode/PlatformIO e rodar build/upload.

Atualizar as "test libs" — MANDATÓRIO antes de qualquer commit
- POR QUE: sketches de test podem depender de libs externas; manter libs sincronizadas evita falhas de build e quebras na CI.
