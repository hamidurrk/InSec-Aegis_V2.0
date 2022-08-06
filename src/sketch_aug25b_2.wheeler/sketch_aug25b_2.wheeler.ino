#include<Servo.h>

 Servo servo;
  
  const int l = 2;
  const int m = 3;
  const int r = 4;

  const int motorB1  = 5; 
  const int motorB2  = 6;  
  const int motorA1  = 10; 
  const int motorA2  = 9;  

  const int trig = 12;
  const int echo = 11;

  const int lights  = 13;

  const int buzzer = 7 ;   

  int i=0;
  int j=0;
  int state;
  int vSpeed=255;     
  int duration = 0;
  int distance = 0;

void followLine ()
{
if(!(digitalRead(l)) && digitalRead(m) && !(digitalRead(r)))                    //(010)
{
      analogWrite(motorA1,255); analogWrite(motorA2, 0);
      analogWrite(motorB1, 255);      analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && digitalRead(r))                    //(001)
{          analogWrite(motorA1, 255); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 100);      analogWrite(motorB2, 0); 
}
if(digitalRead(l) && !(digitalRead(m)) && !(digitalRead(r)))                    //(100)
{     analogWrite(motorA1, 100); analogWrite(motorA2, 0);  
      analogWrite(motorB1, 255);    analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && !(digitalRead(r)))                 //(000)
{
analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
 
}
if(digitalRead(l) && (digitalRead(m) && !(digitalRead(r))))                     //(110)
{
analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
}
  if(digitalRead(r) && (digitalRead(m) && !(digitalRead(l))) )                  //(011)
{
analogWrite(motorA1, 255);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0);   analogWrite(motorB2, 0);   
  }
}

void obstacleAvoid()
{
  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig , LOW);


  duration = pulseIn(echo , HIGH);
  distance = (duration/2) / 28.5 ;
  Serial.println(distance);
  

  if ( distance < 20 )
  {
   analogWrite(motorA1, 0);   analogWrite(motorA2, 255); 
      analogWrite(motorB1, 200); analogWrite(motorB2, 0); 

  }
  else
  {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
  }
 
}

void setup() {

    pinMode(trig , OUTPUT);
    pinMode(echo , INPUT);
    
    pinMode(l, INPUT);
 pinMode(m, INPUT);
 pinMode(r, INPUT);

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(lights, OUTPUT);
    servo.attach(8); 
    Serial.begin(38400);
}
 
void loop() {    if(Serial.available() > 0){     
      state = Serial.read();   
    }
    if (state == 'F' || state == '1') {                                   //forward
         analogWrite(motorA1,255); analogWrite(motorA2, 0);
      analogWrite(motorB1, 255);      analogWrite(motorB2, 0); 
 }
    else if (state == 'G') {                                              //forward_left
       analogWrite(motorA1, 100); analogWrite(motorA2, 0);  
      analogWrite(motorB1, 255);    analogWrite(motorB2, 0); 
   }
    else if (state == 'I') {                                              //forward_right
         analogWrite(motorA1, 255); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 100);      analogWrite(motorB2, 0); 
 }
    else if (state == 'B') {                                              //back
         analogWrite(motorA1, 0); analogWrite(motorA2, 255);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 255); 
   }
     else if (state == 'H') {                                             //back_left
         analogWrite(motorA1, 0); analogWrite(motorA2, 60);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 255); 
   }
    else if (state == 'J') {                                              //back_right
         analogWrite(motorA1, 0); analogWrite(motorA2, 255);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 60); 
   }
    else if (state == 'L') {                                              //left
analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
    }
     else if (state == 'R') {                                              //right
analogWrite(motorA1, 255);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0);   analogWrite(motorB2, 0);     
    }
     else if (state == 'W') {
      obstacleAvoid();
      servo.write (30);
      delay(100);
      servo.write (85);
      delay(100);
      servo.write (150);
      delay(100);
    }
    else if (state == 'V'){
  followLine ();
    }
   else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }

}
