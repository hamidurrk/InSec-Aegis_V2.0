  const int motorA1  = 5;  // Pin  2 of L293
  const int motorA2  = 6;  // Pin  7 of L293
  const int motorB1  = 10; // Pin 10 of L293
  const int motorB2  = 9;  // Pin 14 of L293

  int i=0;
  int j=0;
  int state;
  int vSpeed=200;     // Default speed, from 0 to 255

void setup() {
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    Serial.begin(9600);
}
void loop() {
       analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
delay (5000);
   analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 200);    analogWrite(motorB2, 0); 
delay (5000);
        analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 200); 
delay (5000);
  analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
 delay(5000);
}


