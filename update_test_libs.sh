#!/bin/bash

# Caminho base dos testes
TEST_DIRS=(
    "test/acquisition_test"
    "test/encoder_test"
    "test/motor_test"
)

# Caminhos das pastas originais que serao copiadas
SRC_LIB="lib"
SRC_INCLUDE="include"

echo "Atualizando bibliotecas para pastas de teste..."

# Loop por cada pasta de teste
for TEST_PATH in "${TEST_DIRS[@]}"; do
    echo ""
    echo "Processando: $TEST_PATH"

    # Remove pastas antigas de lib e include se existirem
    rm -rf "$TEST_PATH/lib"
    rm -rf "$TEST_PATH/include"

    # Copia as pastas novas
    cp -r "$SRC_LIB" "$TEST_PATH/lib"
    cp -r "$SRC_INCLUDE" "$TEST_PATH/include"

    echo "Copiado lib/ e include/ para $TEST_PATH"
done

echo ""
echo "Finalizado!"
