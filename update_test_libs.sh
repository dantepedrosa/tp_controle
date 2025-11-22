#!/bin/bash

# Pastas de teste
TEST_DIR_ACQ="test/acquisition_test"
TEST_DIR_ENCODER="test/encoder_test"
TEST_DIR_MOTOR="test/motor_test"

# Origem das libs
SRC_LIB="lib"
SRC_INCLUDE="include"

echo "Atualizando bibliotecas para testes..."

######################################
# 1) TESTE DE AQUISICAO (COMPLETO)
######################################
echo ""
echo "[ACQUISITION TEST]"

# Limpa os arquivos antigos
rm -f $TEST_DIR_ACQ/*.h
rm -f $TEST_DIR_ACQ/*.cpp

# Copia config.h
cp $SRC_INCLUDE/config.h $TEST_DIR_ACQ/

# Copia data_logger
cp $SRC_LIB/data_logger/data_logger.h $TEST_DIR_ACQ/
cp $SRC_LIB/data_logger/data_logger.cpp $TEST_DIR_ACQ/

# Copia encoder
cp $SRC_LIB/encoder/encoder.h $TEST_DIR_ACQ/
cp $SRC_LIB/encoder/encoder.cpp $TEST_DIR_ACQ/

# Copia motor
cp $SRC_LIB/motor/motor.h $TEST_DIR_ACQ/
cp $SRC_LIB/motor/motor.cpp $TEST_DIR_ACQ/

echo "Arquivos copiados para $TEST_DIR_ACQ"


######################################
# 2) ENCODER TEST (SO ENCODER + CONFIG)
######################################
echo ""
echo "[ENCODER TEST]"

rm -f $TEST_DIR_ENCODER/*.h
rm -f $TEST_DIR_ENCODER/*.cpp

cp $SRC_INCLUDE/config.h $TEST_DIR_ENCODER/
cp $SRC_LIB/encoder/encoder.h $TEST_DIR_ENCODER/
cp $SRC_LIB/encoder/encoder.cpp $TEST_DIR_ENCODER/

echo "Arquivos copiados para $TEST_DIR_ENCODER"


######################################
# 3) MOTOR TEST (SO MOTOR + CONFIG)
######################################
echo ""
echo "[MOTOR TEST]"

rm -f $TEST_DIR_MOTOR/*.h
rm -f $TEST_DIR_MOTOR/*.cpp

cp $SRC_INCLUDE/config.h $TEST_DIR_MOTOR/
cp $SRC_LIB/motor/motor.h $TEST_DIR_MOTOR/
cp $SRC_LIB/motor/motor.cpp $TEST_DIR_MOTOR/

echo "Arquivos copiados para $TEST_DIR_MOTOR"

echo ""
echo "Finalizado com sucesso!"
