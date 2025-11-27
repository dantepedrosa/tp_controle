/*
  ============================================
  UFMG BIA-Kit is placed under the MIT License
  Copyright (c) 2024 by GTI (UFMG)
  ============================================
  Hardware:
  * ESP-WROOM-32 30 pin development board
  * 2 Nidec 24-H
  * 2 Set Tire wheel 88516 + 88517
  * 1 2GT-280 belt, width 6mm
  * 1 All-Metal Gear Servo SG90
  * 1 DC(12V)-DC(5V) Adjustable Linear Regulator 
  * 1 Module GY-521 MPU-6050
  * 1 Power Bank Box Charger, DC 12V output, 3x18650 batteries
*/

// I2C libray communication
#include <Wire.h>

// ENCODER library based on the built in counter hardware
#include <ESP32Encoder.h>

// ESP32 BLUE LED pin
#define INTERNAL_LED 2

// NIDEC PWM config
#define NIDEC_TIMER_BIT   8
#define NIDEC_BASE_FREQ   20000

// NIDEC pins: Reaction Wheel Motor
#define BRAKE1             4 //Yellow wire (Start/Stop)
#define NIDEC1_PWM        16 //Write wire  (PWM)
#define DIR1              17 //Green wire  (Forward/Reverse) 
#define ENCA_1            18 //Brown wire  (Signal A)  
#define ENCB_1            19 //Orange      (Signal B)  
#define NIDEC1_PWM_CH      1

// Encoder var
ESP32Encoder NIDEC1_ENC;

// Global Control vars
//    dwheel       wheel 
int   error_int = 0;     
float Ts = 0.1, experimentT = 10.0, currentT = 0.0, previousT = 0.0;      // Elapsed time in loop() function

// MAIN SETUP
void setup() { // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);                   // make sure your Serial Monitor is also set at this baud rate.

  NIDECsetup();

  pinMode(INTERNAL_LED,OUTPUT);

  currentT = millis();  
}

// MAIN LOOP
void loop() {// put your main code here, to run repeatedly:
  
  currentT = millis();
   
  if ((currentT - previousT)/1000.0 >= Ts) {
    previousT = currentT;
  
    if (currentT/1000.0 < experimentT){
      
      digitalWrite(BRAKE1, HIGH);
      
      // 1: constant reference
      int set_point = 300; // speed desired
      // // multi-step reference signal

      // if (currentT/1000.0 >= experimentT/3 && currentT/1000.0 < 2*experimentT/3 ){
      // set_point = 600;
      // }
      // else if (currentT/1000.0 >= 2*experimentT/3){
      // set_point = 900;
      // } 

      // 2: reading speed sensor
      int wheel_speed = NIDEC1_ENC.getCount(); //reaction wheel speed
      NIDEC1_ENC.clearCount();

      // 3a - CL  Proportional (P) control
      // int error = set_point - wheel_speed;
      // int pwm = constrain(10 * error, -255, 255); 

      // // 3b - CL Proportional Integral (PI) control
      int error = set_point - wheel_speed;
      error_int += error*Ts;    
      int pwm = constrain(1 * error + 1 * error_int, -255, 255); 
      
      // 4 - motor command
      MOTOR1cmd(pwm);
      
      // 5 - Print outputs
      Serial.print(currentT);
      Serial.print(",");
      Serial.print(pwm);
      Serial.print(",");
      Serial.println(wheel_speed);

    } else { 
      digitalWrite(INTERNAL_LED,HIGH);  
      MOTOR1cmd(0);      // stop reaction wheel 
    }
  }   
  
}


void NIDECsetup(){
  pinMode(BRAKE1, OUTPUT);
  digitalWrite(BRAKE1, HIGH);
  
  pinMode(DIR1, OUTPUT);
  ledcSetup(NIDEC1_PWM_CH, NIDEC_BASE_FREQ, NIDEC_TIMER_BIT);
  ledcAttachPin(NIDEC1_PWM, NIDEC1_PWM_CH);
  MOTOR1cmd(0);
  
  // Encoder setup
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
	NIDEC1_ENC.attachFullQuad(ENCA_1, ENCB_1);
  NIDEC1_ENC.clearCount();

}

// NIDEC functions
void MOTOR1cmd(int sp) {
  if (sp < 0) {
    digitalWrite(DIR1, LOW);
    sp = -sp;
  } else {
    digitalWrite(DIR1, HIGH);
  }
  ledcWrite(NIDEC1_PWM_CH, int(sp > 255 ? 255 : 255 - sp));
}
