# Configurando Arduino IDE para NodeMCU V3 (ESP8266)

Este guia rápido descreve como preparar o Arduino IDE para compilar e enviar sketches para NodeMCU V3 (ESP8266).

1) Instalar o suporte ao ESP8266 no Arduino IDE
- Abra `Arquivo -> Preferências`.
- Em "URLs adicionais para gerenciadores de placas", adicione (se ainda não existir):
  - http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Clique em "OK".
- Abra `Ferramentas -> Placa -> Gerenciador de Placas` e procure por "esp8266". Instale "esp8266 by ESP8266 Community".

2) Selecionar placa e porta
- Em `Ferramentas -> Placa`, escolha: "NodeMCU 1.0 (ESP-12E Module)" (funciona para NodeMCU V3).
- Selecione a `Porta` correta no menu `Ferramentas -> Porta`.

3) Drivers (se necessário)
- NodeMCU / clones geralmente usam chip CH340/CP2102. Instale drivers correspondentes ao seu adaptador USB.

4) Ajustes recomendados
- `Upload Speed`: mantenha padrão (115200) para uploads. O baud rate usado pelo `Serial` é configurado no sketch (este projeto usa `Serial.begin(9600)`).
- `Flash Size`: 4M (1M SPIFFS) costuma ser uma boa opção.

5) Observações sobre pinos e boot
- Alguns pinos (GPIO0, GPIO2, GPIO15) afetam o modo de boot do ESP8266. Evite usá-los para entradas/saídas críticas no boot.
- Se usar o encoder em um desses pinos, teste o comportamento de boot antes de montar final.

6) PWM no ESP8266
- O core ESP8266 expõe `analogWrite(pin, value)`, mas a faixa padrão pode ser 0..1023. O projeto chama `analogWriteRange(255)` em `Motor::begin()` para usar 0..255.

7) Carregar e monitorar
- Carregue o sketch normalmente (`Sketch -> Upload`).
- Abra o Monitor Serial (`Ferramentas -> Monitor Serial`) e selecione `9600 baud` para ver a telemetria do sketch criado aqui.

Se quiser, eu posso fornecer um script de verificação para testar os PWM e leitura do encoder de forma automatizada.
