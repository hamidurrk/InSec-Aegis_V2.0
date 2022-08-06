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

  const float maxBattery = 8.0;
  int perVolt;               
  float voltage = 0.0;        
  int level;

  long previousMillis = -1000*10;
  long interval = 1000*10;     
  unsigned long currentMillis;   

  int i=0;
  int j=0;
  int state;
  int vSpeed=255;    
  int duration = 0;
  int distance = 0;

void followLine ()
{
if(!(digitalRead(l)) && digitalRead(m) && !(digitalRead(r))) //(010)
{
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && digitalRead(r))//(001)
{       analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 200); 
}
if(digitalRead(l) && !(digitalRead(m)) && !(digitalRead(r)))//(100)
{
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
      analogWrite(motorB1, 200);    analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && !(digitalRead(r)))//(000)
{
analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
 
}
if(digitalRead(l) && (digitalRead(m) && !(digitalRead(r))))//(110)
{
analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 200); analogWrite(motorB2, 0); 
}
  if(digitalRead(r) && (digitalRead(m) && !(digitalRead(l))) )//(011)
{
analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0);   analogWrite(motorB2, 200);     
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
 
void loop() {
 
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
 
    if (state == '0'){
      vSpeed=0;}
    else if (state == '1'){
      vSpeed=100;}
    else if (state == '2'){
      vSpeed=180;}
    else if (state == '3'){
      vSpeed=200;}
    else if (state == '4'){
      vSpeed=255;}
     
    if (state == 'F' || state == '1') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    }
    else if (state == 'G') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
        digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
    else if (state == 'I') {
        analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
    }
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
    digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    }
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
    }
    else if (state == 'L') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
       digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
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
    currentMillis = millis();
    if(currentMillis - (previousMillis) > (interval)) {
       previousMillis = currentMillis; 
 
       voltage = (analogRead(A0)*5.015 / 1024.0)*11.132;
   
       perVolt = (voltage*100)/ maxBattery;
       if      (perVolt<=75)               { level=0; }
       else if (perVolt>75 && perVolt<=80) { level=1; }   
       else if (perVolt>80 && perVolt<=85) { level=2; }  
       else if (perVolt>85 && perVolt<=90) { level=3; }  
       else if (perVolt>90 && perVolt<=95) { level=4; }  
       else if (perVolt>95)                { level=5; }   
       Serial.println(level);    
    }   
}
