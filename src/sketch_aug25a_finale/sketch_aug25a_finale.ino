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
   analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
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
    Serial.begin(38400);
}
 
void loop() {

    if(Serial.available() > 0)
    {     
      state = Serial.read();   
      Serial.println(state);
    }
  
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
      if (i==0){  
         digitalWrite(lights, HIGH); 
         i=1;
      }
      else if (i==1){
         digitalWrite(lights, LOW); 
         i=0;
      }
      state='n';
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

   
}
