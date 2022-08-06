#include<Servo.h>

 Servo servo;
  
  const int l = 2;
  const int m = 3;
  const int r = 4;
//L293 Connection   
  const int motorB1  = 5;  // Pin  2 of L293
  const int motorB2  = 6;  // Pin  7 of L293
  const int motorA1  = 10; // Pin 10 of L293
  const int motorA2  = 9;  // Pin 14 of L293

  const int trig = 12;
  const int echo = 11;
//Leds connected to Arduino UNO Pin 12
  const int lights  = 13;
//Buzzer / Speaker to Arduino UNO Pin 3
  const int buzzer = 7 ;   
//Calculate Battery Level
  const float maxBattery = 8.0;// Change value to your max battery voltage level! 
  int perVolt;                 // Percentage variable 
  float voltage = 0.0;         // Read battery voltage
  int level;
// Use it to make a delay... without delay() function!
  long previousMillis = -1000*10;// -1000*10=-10sec. to read the first value. If you use 0 then you will take the first value after 10sec.  
  long interval = 1000*10;       // interval at which to read battery voltage, change it if you want! (10*1000=10sec)
  unsigned long currentMillis;   //unsigned long currentMillis;
//Useful Variables
  int i=0;
  int j=0;
  int state;
  int vSpeed=255;     // Default speed, from 0 to 255
  int duration = 0;
  int distance = 0;

void followLine ()
{
if(!(digitalRead(l)) && digitalRead(m) && !(digitalRead(r))) // Move Forward (010)
{
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && digitalRead(r))// Turn medium right (001)
{       analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 200); 
}
if(digitalRead(l) && !(digitalRead(m)) && !(digitalRead(r)))// turn medium left (100)
{
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
      analogWrite(motorB1, 200);    analogWrite(motorB2, 0); 
}
if(!(digitalRead(l)) && !(digitalRead(m)) && !(digitalRead(r)))// stop (000)
{
analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
 
}
if(digitalRead(l) && (digitalRead(m) && !(digitalRead(r))))// Turn Sharp left 90 degree (110)
{
analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
      analogWrite(motorB1, 200); analogWrite(motorB2, 0); 
}
  if(digitalRead(r) && (digitalRead(m) && !(digitalRead(l))) )// Turn Sharp Right 90 degree (011)
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
 //Save income data to variable 'state'
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
 //Change speed if state is equal from 0 to 4. Values must be from 0 to 255 (PWM)
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
     
  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward!
    if (state == 'F' || state == '1') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'G', car will go forward left
    else if (state == 'G') {
      analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
        digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
  /**********************Forward Right************************/
  //If state is equal with letter 'I', car will go forward right
    else if (state == 'I') {
        analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
    }
  /***********************Backward****************************/
  //If state is equal with letter 'B', car will go backward
    else if (state == 'B') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
    digitalWrite(motorB1, LOW);      digitalWrite(motorB2, LOW); 
    }
  /**********************Backward Left************************/
  //If state is equal with letter 'H', car will go backward left
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
  /**********************Backward Right************************/
  //If state is equal with letter 'J', car will go backward right
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
    }
  /***************************Left*****************************/
  //If state is equal with letter 'L', wheels will turn left
    else if (state == 'L') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
       digitalWrite(motorB1, HIGH);      digitalWrite(motorB2, LOW); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', wheels will turn right
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        digitalWrite(motorB1, LOW);      digitalWrite(motorB2, HIGH); 
    }
  /************************Lights*****************************/
  //If state is equal with letter 'W', turn leds on or of off
    else if (state == 'W') {
      obstacleAvoid();
      servo.write (30);
      delay(100);
      servo.write (85);
      delay(100);
      servo.write (150);
      delay(100);
    }
  /**********************Horn sound***************************/
  //If state is equal with letter 'V', play (or stop) horn sound
    else if (state == 'V'){
  followLine ();
    }
  /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }
  /***********************Battery*****************************/
  //Read battery voltage every 10sec.
    currentMillis = millis();
    if(currentMillis - (previousMillis) > (interval)) {
       previousMillis = currentMillis; 
       //Read voltage from analog pin A0 and make calibration:
       voltage = (analogRead(A0)*5.015 / 1024.0)*11.132;
       //Calculate percentage...
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
