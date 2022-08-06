   #include <Servo.h>

   Servo frontServo;
   Servo rearServo;
   int centerPos = 90;
   int frontRightUp = 72;
   int frontLeftUp = 108;
   int backRightForward = 75;
   int backLeftForward = 105;

   void moveBackRight() 
   {
    frontServo.write(frontRightUp);
    rearServo.write(backRightForward-6);
    delay(125);
    frontServo.write(centerPos);
    rearServo.write(centerPos-6);
    delay(65);
    frontServo.write(frontLeftUp+9);
    rearServo.write(backLeftForward-6);
    delay(125);
    frontServo.write(centerPos);
    rearServo.write(centerPos);
    delay(65);
   }

   void setup()
   {
    frontServo.attach(2);
    rearServo.attach(3);
   }

   void loop()
   {
    moveBackRight();
    delay(150); //time between each step taken, speed of walk
   }