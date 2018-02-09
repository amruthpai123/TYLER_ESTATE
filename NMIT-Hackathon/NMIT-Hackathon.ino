#include<Servo.h>
Servo myServo;

int mode;
int duration[2],distance[2];
int velocity = 200;
int motorPins[4]={A0,A1,A2,A3};
int echo[2]={12,14},trigger[2]={13,15};
int servoMotorPin = 7;

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++)
    pinMode(motorPins[i],OUTPUT);
  for(int i = 0;i<2;i++)
  {
    pinMode(echo[i],INPUT);
    pinMode(trigger[i],OUTPUT);
  }
  mode =5;
  myServo.attach(servoMotorPin);
  Serial.begin(9600);
    
}

void controlMotors()
{
  if(mode == 5)
  {
    analogWrite(motorPins[0],0);
    analogWrite(motorPins[1],0);
    analogWrite(motorPins[2],0);
    analogWrite(motorPins[3],0);
  }
  else if(mode ==2)
  {
    analogWrite(motorPins[0],velocity);
    analogWrite(motorPins[1],0);
    analogWrite(motorPins[2],0);
    analogWrite(motorPins[3],velocity);
  }

  else if(mode ==8)
  {
    analogWrite(motorPins[0],0);
    analogWrite(motorPins[1],velocity);
    analogWrite(motorPins[2],velocity);
    analogWrite(motorPins[3],0);
  }
  else if(mode ==4)
  {
    analogWrite(motorPins[0],velocity);
    analogWrite(motorPins[1],0);
    analogWrite(motorPins[2],velocity);
    analogWrite(motorPins[3],0);
  }
  else if(mode ==6)
  {
    analogWrite(motorPins[0],0);
    analogWrite(motorPins[1],velocity);
    analogWrite(motorPins[2],0);
    analogWrite(motorPins[3],velocity);
  }
}

void scan()
{
  for(int i=0;i<180;i++)
  {
    myServo.write(i);
    delay(10);
  }
  for(int i=180;i>0;i--)
  {
    myServo.write(i);
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<2;i++)
  {
    digitalWrite(trigger[i],LOW);
    digitalWrite(trigger[i],HIGH);
    digitalWrite(trigger[i],LOW);
    duration[i] = pulseIn(echo[i],HIGH);
    distance[i] = (duration[i]/2)/29.1;
  }
  mode = Serial.read();
  if(distance[0]<=30 || distance[1]<=30)
  {
    reenter:
    mode = 5;
    controlMotors();
    mode=Serial.read();
    if(distance[0]<=30 && mode ==2)
    {
      scan();
      goto reenter;
    }
    if(distance[1]<=30 && mode ==8)
      goto reenter;
      
  }
  controlMotors();
}


