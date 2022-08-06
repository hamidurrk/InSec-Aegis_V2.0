   #include <Servo.h>

   Servo frontServo;
   Servo rearServo;
   /* Servo motors - global variables */ 
   int centerPos = 90;
   int frontRightUp = 72;
   int frontLeftUp = 108;
   int backRightForward = 75;
   int backLeftForward = 105;
   int walkSpeed = 150; // How long to wait between steps in milliseconds
   int centerTurnPos = 81;
   int frontTurnRightUp = 63;
   int frontTurnLeftUp = 117;
   int backTurnRightForward = 66;
   int backTurnLeftForward = 96;

   /* Ping distance measurement - global variables */
   int pingPin = 4;
   long int duration, distanceInches;
   long distanceFront=0; //cm
   int startAvoidanceDistance=20; //cm

   long microsecondsToInches(long microseconds)
   {
    return microseconds / 74 / 2;
   }

   long microsecondsToCentimeters(long microseconds)
   {
    return microseconds / 29 / 2;
   }

   long distanceCm(){ 
              pinMode(pingPin, OUTPUT);
              digitalWrite(pingPin, LOW);
              delayMicroseconds(2);
              digitalWrite(pingPin, HIGH);
              delayMicroseconds(5);
              digitalWrite(pingPin, LOW);

              pinMode(pingPin, INPUT);
              duration = pulseIn(pingPin, HIGH);

              distanceInches = microsecondsToInches(duration);
              return microsecondsToCentimeters(duration);
             }

             void center()
             {
               frontServo.write(centerPos);
               rearServo.write(centerPos);
             }

             void moveForward() 
             {
               frontServo.write(frontRightUp);
               rearServo.write(backLeftForward);
               delay(125);
               frontServo.write(centerPos);
               rearServo.write(centerPos);
               delay(65);
               frontServo.write(frontLeftUp);
               rearServo.write(backRightForward);
               delay(125);

               frontServo.write(centerPos);
               rearServo.write(centerPos);
               delay(65);
              }

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

               void moveTurnLeft()
               {
                 frontServo.write(frontTurnRightUp);
                 rearServo.write(backTurnLeftForward);
                 delay(125);
                 frontServo.write(centerTurnPos);
                 rearServo.write(centerTurnPos);
                 delay(65);
                 frontServo.write(frontTurnLeftUp);
                 rearServo.write(backTurnRightForward);
                 delay(125);

                 frontServo.write(centerTurnPos);
                 rearServo.write(centerTurnPos);
                 delay(65);
                }

                void setup() 
                {
                  frontServo.attach(2);
                  rearServo.attach(3);
                  pinMode(pingPin, OUTPUT);
                }

                void loop() 
                {
                  distanceFront=distanceCm(); 
                  if (distanceFront > 1){ // Filters out any stray 0.00
                   if (distanceFront<startAvoidanceDistance) { 
                    for(int i=0; i<=8; i++) { 
                      moveBackRight();
                      delay(walkSpeed);
                    }
                  for(int i=0; i<=10; i++) {
                   moveTurnLeft();
                   delay(walkSpeed);
                  }
                } else {
                  moveForward(); 
                  delay(walkSpeed);
                 }
                }
               }