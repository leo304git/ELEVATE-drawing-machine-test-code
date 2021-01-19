#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>

#define Stepper_Enable_Pin 10

#define dirPin_X 4
#define stepPin_X 2
#define dirPin_Y 5
#define stepPin_Y 3
#define motorInterfaceType 1
#define servoPin 9
#define Servo_Pen_Up_Angle    30
#define Servo_Pen_Down_Angle  0
#define endStopPin_X 11 
#define endStopPin_Y 12

#define X_Milis_Per_Step    0.01
#define Y_Milis_Per_Step    0.01

#define Positive HIGH
#define Negative LOW

AccelStepper stepper_X = AccelStepper(motorInterfaceType, stepPin_X, dirPin_X);
AccelStepper stepper_Y = AccelStepper(motorInterfaceType, stepPin_Y, dirPin_Y);
MultiStepper steppers;
Servo servo_Z;

bool end_stop_X = false;
bool end_stop_Y = false;
int count = 0;
bool p = false;

void setup() {
  Serial.begin(9600);
  pinMode(Stepper_Enable_Pin, OUTPUT);
  pinMode(dirPin_X, OUTPUT);
  pinMode(stepPin_X, OUTPUT);
  pinMode(dirPin_Y, OUTPUT);
  pinMode(stepPin_Y, OUTPUT);
  pinMode(endStopPin_X, INPUT);
  pinMode(endStopPin_Y, INPUT);
  servo_Z.attach(servoPin);
  servo_Z.write(Servo_Pen_Up_Angle);
  delay(1000);
  servo_Z.write(0);
  delay(1000);
  //Serial.println(count);
  servo_Z.write(Servo_Pen_Up_Angle);
  delay(1000);
  servo_Z.write(0);
  delay(1000);
  //Serial.println(Servo_Pen_Up_Angle);
  digitalWrite(Stepper_Enable_Pin, LOW);
  //digitalWrite(dirPin_X, HIGH);
  //digitalWrite(dirPin_Y, LOW);
}

void loop() {
 
  //Serial.println(count);
  if(count >= 1000){
    digitalWrite(dirPin_X, Negative);
    digitalWrite(dirPin_Y, Positive);
    p = true;
  }
  if(count <= 0){
    digitalWrite(dirPin_X, Positive);
    digitalWrite(dirPin_Y, Negative);
    p = false;
  }
  if(!end_stop_X)
    end_stop_X = digitalRead(endStopPin_X);
  if(!end_stop_Y)
    end_stop_Y = digitalRead(endStopPin_Y);

  if(!end_stop_X)
    digitalWrite(stepPin_X, HIGH);
  delayMicroseconds(250);
  if(!end_stop_Y)
    digitalWrite(stepPin_Y, HIGH);
  delayMicroseconds(250);
  digitalWrite(stepPin_X, LOW);
  delayMicroseconds(250);
  digitalWrite(stepPin_Y, LOW);
  delayMicroseconds(250);
  
  if(p)
    count -= 1;
  else
    count += 1;
}
