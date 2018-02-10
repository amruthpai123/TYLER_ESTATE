#include <dht.h>
#define trig_pin 12
#define echo_pin 13
#define DHT11_PIN 7
int mapped_array[30][30]={0};
int mode=5;
int duration,distance,chk;
int velocity = 130;
int I1=A0,I2=A1,I3=A2,I4=A3;
boolean unsafe=0;
//dht DHT;

void moveleft()
{   analogWrite(I1,velocity);
    analogWrite(I2,0);
    analogWrite(I3,velocity);
    analogWrite(I4,0);
  
}
void moveright()
{
              analogWrite(I1,0);
             analogWrite(I2,velocity);
             analogWrite(I3,0);
             analogWrite(I4,velocity);
}
void controlMotors()
{
  switch(mode)
  {
    case 2:  analogWrite(I1,velocity);
             analogWrite(I2,0);
             analogWrite(I3,0);
             analogWrite(I4,velocity);
             break;
    case 8:  analogWrite(I1,0);
             analogWrite(I2,velocity);
             analogWrite(I3,velocity);
              analogWrite(I4,0);
              break;
    case 4: moveleft();
             delay(500);
             break;
    case 6: moveright(); 
             delay(500);
             break;
    case 5:  analogWrite(I1,0);
             analogWrite(I2,0);
             analogWrite(I3,0);
             analogWrite(I4,0);
             break;
  }
  
 
}

 void move_back()
     {  for(int i=0;i<200;i++)
         {analogWrite(I1,velocity);
         analogWrite(I2,0);
         analogWrite(I3,0);
         analogWrite(I4,velocity);
         }
     }
    void check1()
     { 
       for(int i=0;i<1000;i++)
       {analogWrite(I1,0);
       analogWrite(I2,velocity);
       analogWrite(I3,0);
       analogWrite(I4,velocity); 
       }
     }
     void stop1()
     {
       analogWrite(I1,0);
    analogWrite(I2,0);
    analogWrite(I3,0);
    analogWrite(I4,0);
     }
void setup() {
  // put your setup code here, to run once:
  pinMode(I1,OUTPUT);
  pinMode(I2,OUTPUT);
  pinMode(I3,OUTPUT);
  pinMode(I4,OUTPUT);
  
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  
  mode =5;
  Serial.begin(9600);
}

void loop() 
{
    
    digitalWrite(trig_pin,LOW);
    //delay(20);
    digitalWrite(trig_pin,HIGH);
    //delay(20);
    digitalWrite(trig_pin,LOW);
    duration=pulseIn(echo_pin,HIGH);
    distance=(duration/2)/29.1;
   // if(Serial.available()>0)
    //    mode=Serial.read();
   // controlMotors();
  if(distance<50 && distance >0)
    { 
         mode=5;
         controlMotors();
         delay(500);
         mode=2;
         controlMotors();
         delay(500);
         mode=5;
         controlMotors();
        
      
    }
  
    else
    {    // mode=5;
          
         if(Serial.available()>0)
        {   mode=Serial.read();  
             controlMotors();
             
        } 
      //  else
      //  goto x;
    }
    
}    
