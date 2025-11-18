#include "config.h"
#include "Motor.h"
#include "Encoder.h"
#include "PID.h"

// Instâncias (ajuste pinos em config.h)
Motor leftMotor(LEFT_PWM, LEFT_IN1, LEFT_IN2);
Motor rightMotor(RIGHT_PWM, RIGHT_IN1, RIGHT_IN2);
Encoder wheelEncoder(ENCODER_PIN);
PID forwardPid(1.0, 0.0, 0.0); // parâmetros iniciais (P apenas)

const float targetDistanceMeters = 5.0; // distância alvo

void setup() {
  // Usando 9600 bps conforme solicitado (monitor serial em 9600)
  Serial.begin(9600);
  delay(200);
  Serial.println("Inicializando robô - esqueleto de controle (ESP8266, 9600bps)");

  leftMotor.begin();
  rightMotor.begin();
  wheelEncoder.begin();

  forwardPid.setOutputLimits(-255, 255);

  wheelEncoder.reset();
}

void loop() {
  float distance = wheelEncoder.getDistanceMeters();
  float error = targetDistanceMeters - distance;

  if (error <= 0) {
    leftMotor.stop();
    rightMotor.stop();
    Serial.println("Percurso concluido");
    while (true) { delay(1000); }
  }

  int power = (int)forwardPid.compute(error);
  power = constrain(power, -255, 255);

  // Simples: aplica mesmo comando nas duas rodas (assume alinhamento)
  leftMotor.setSpeed(power);
  rightMotor.setSpeed(power);

  // Telemetria básica
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 250) {
    lastPrint = millis();
    Serial.print("dist(m)="); Serial.print(distance, 3);
    Serial.print("  erro="); Serial.print(error,3);
    Serial.print("  pwm="); Serial.println(power);
  }

  delay(10);
}
