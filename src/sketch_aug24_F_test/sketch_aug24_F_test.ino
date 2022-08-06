 const int motorA1  = 9;
  const int motorA2  = 8;
  const int motorB1  = 5;
  const int motorB2  = 6; 
  const int enB = 10;
  int vSpeed = 255;

void test_1()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);

  delay(500);

  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);

  delay(500);
}

void test_2()
{
  digitalWrite(motorB1, HIGH);
  analogWrite(motorB2, 0);


}
  void setup()
{
   pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    Serial.begin(9600);
} 
void loop()
{
  test_1();
  delay(100);
}

