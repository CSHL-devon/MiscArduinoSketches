#include <Servo.h>

//This sketch is for controlling the servos attached to the reward-delivery spouts of two behavior rigs attached
//to the same microcontroller (in this case, an Arduino Mega 2560). A single wire trigger is used for each servo
//in order to conserve wire outputs on the controlling Bpods.
//
//Devon Cowan, CSHL, 2020

//SpoutServo_1 is for upper rig, SpoutServo_2 is for lower
Servo SpoutServo_1;
Servo SpoutServo_2;

//Top and bottom servo positions are triggered by same wire. Initialize to Lower state (0)
int Servo_1_State = 0;
int Servo_2_State = 0;

const int TriggerPin_1 = 2;
const int TriggerPin_2 = 3;
const int CmndPin_1 = 4;
const int CmndPin_2 = 5;
const int UpPulse = 1350;
const int DownPulse = 1250;

void setup() {
  
  //Set pins to carry pulses to servos. CmndPin_1 is for upper rig, CmndPin_2 is for lower
  SpoutServo_1.attach(CmndPin_1);
  SpoutServo_2.attach(CmndPin_2);

  //Set spouts to bottom position
  SpoutServo_1.writeMicroseconds(DownPulse);
  SpoutServo_2.writeMicroseconds(DownPulse);

  //TriggerPin_1 is for upper rig, TriggerPin_2 is for lower
  pinMode(TriggerPin_1, INPUT_PULLUP);
  pinMode(TriggerPin_2, INPUT_PULLUP);

  //Set conditions for interrupt
  attachInterrupt(digitalPinToInterrupt(TriggerPin_1), Servo_1, RISING);
  attachInterrupt(digitalPinToInterrupt(TriggerPin_2), Servo_2, RISING);
}

void loop() {
}

//Control Servo 1 (upper rig)
void Servo_1() {
  if (Servo_1_State == 1){
    SpoutServo_1.writeMicroseconds(DownPulse);
    Servo_1_State = 0;
    }
  else{
    SpoutServo_1.writeMicroseconds(UpPulse);
    Servo_1_State = 1;
  }
}

//Control Servo 2 (lower rig)
void Servo_2() {
  if (Servo_2_State == 1){
    SpoutServo_2.writeMicroseconds(DownPulse);
    Servo_2_State = 0;
    }
  else{
    SpoutServo_2.writeMicroseconds(UpPulse);
    Servo_2_State = 1;
  }
}
