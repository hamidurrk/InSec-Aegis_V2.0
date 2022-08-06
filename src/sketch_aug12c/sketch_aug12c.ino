  #include <Servo.h>

   Servo frontServo;
   Servo rearServo;
   int centerPos = 90;  
   int frontRightUp = 72;  
   int frontLeftUp = 108;  
   int backRightForward = 75;  
   int backLeftForward = 105;
   int walkSpeed = 150;

   int trigPin = 9;
   int echoPin = 10;
   long int duration, distanceInches;
   long distanceFront = 0;             //cm
   int startAvoidanceDistance=20;         //cm


   long microsecondsToInches(long microseconds)

   {
    return microseconds / 74 / 2;
   }


   long microsecondsToCentimeters(long microseconds)
   {
    return microseconds / 29 / 2;
   }


   long distanceCm()
   
   {  
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

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
    

void moveBackward()  

   {
    frontServo.write(frontRightUp);
        rearServo.write(backRightForward);
        delay(125);
        
    frontServo.write(centerPos);
       rearServo.write(centerPos);
        delay(65);
    
    frontServo.write(frontLeftUp);
        rearServo.write(backLeftForward);
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

void moveBackLeft()  
   
   {
        frontServo.write(frontRightUp);
        rearServo.write(backRightForward+6);
        delay(125);
    
    frontServo.write(centerPos);
        rearServo.write(centerPos+6);
        delay(65);
    
    frontServo.write(frontLeftUp-9);
        rearServo.write(backLeftForward+6);
        delay(125);
    
    frontServo.write(centerPos);
        rearServo.write(centerPos);
        delay(65);
   }


void moveTurnLeft()  
   
   {
        frontServo.write(frontRightUp-9);
        rearServo.write(backLeftForward-9);
        delay(125);
    
    frontServo.write(centerPos-9);
        rearServo.write(centerPos-9);
        delay(65);
        
    frontServo.write(frontLeftUp+9);
        rearServo.write(backRightForward-9);
        delay(125);
        
    frontServo.write(centerPos-9);
        rearServo.write(centerPos-9);
        delay(65);
   }


void moveTurnRight()

   {
    frontServo.write(frontRightUp+9);
        rearServo.write(backLeftForward+9);
        delay(125);
    
    frontServo.write(centerPos+9);
        rearServo.write(centerPos+9);
        delay(65);
        
    frontServo.write(frontLeftUp-9);
        rearServo.write(backRightForward+9);
        delay(125);
        
    frontServo.write(centerPos+9);
        rearServo.write(centerPos+9);
        delay(65);
   }
void startPatrol()
   {
   distanceFront=distanceCm();  
                  if (distanceFront > 1)
              {                 // Filters out any stray 0.00 error readings
  
                   if (distanceFront<startAvoidanceDistance) 
            {  
                    for(int i=0; i<=8; i++) 
               {  
                      moveBackRight();
                      delay(walkSpeed);
                       }
                 for(int i=0; i<=10; i++) 
                {
                   moveTurnLeft();
                   delay(walkSpeed);
                        }
            }
           else
            {
            moveForward();
            delay(walkSpeed);
            }
           }
}

void Stop()
{
  frontServo.write(centerPos);
  rearServo.write(centerPos);
}


void setup()
   
   {
    frontServo.attach(2);
    rearServo.attach(3);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
   }

void loop()

   {
    while(Serial.available())
    {
       char In=Serial.read();
       Serial.println(In);
        
       if(In=='p' || In=='P')
        {
                  distanceFront=distanceCm();  
                  if (distanceFront > 1)
              {                 // Filters out any stray 0.00 error readings
  
                   if (distanceFront<startAvoidanceDistance) 
            {  
                    for(int i=0; i<=8; i++) 
               {  
                      moveBackRight();
                      delay(walkSpeed);
                       }
                 for(int i=0; i<=10; i++) 
                {
                   moveTurnLeft();
                   delay(walkSpeed);
                        }
            }
           else 
            {
            moveForward();
            delay(walkSpeed);
            }
           }
        }
       else if(In=='w' || In=='W')
        {
           moveForward();  
                   delay(walkSpeed);
        } 
       else if(In=='x' || In=='X')
        {
           moveBackward();
           delay(walkSpeed);
        }
       else if(In=='a' || In=='A')
        {
           moveTurnLeft();
           delay(walkSpeed);
        }
       else if(In=='d' || In=='D')
        {
           moveTurnRight();
           delay(walkSpeed);
        }
       else if(In=='z' || In=='Z')
        {
           moveBackLeft();
           delay(walkSpeed);
        }
       else if(In=='c' || In=='C')
        {
           moveBackRight();
           delay(walkSpeed);
        }
       else if (In=='o' || In=='O')
        {
          startPatrol();
          delay(walkSpeed);
        }
       else 
        {
           center();
        }
    }
   }
