  #include <Servo.h>

   Servo frontServo;
   
   int centerPos = 90;  
   int frontRightUp = 50;  
   int frontLeftUp = 130;  
   int backRightForward = 75;  
   int backLeftForward = 105;
   int walkSpeed = 60;
   int Pin = 13;

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
   }
 
void moveForward()  

   {
        digitalWrite(Pin, LOW);
        frontServo.write(frontRightUp);
        delay(125);
        
        frontServo.write(centerPos);
        delay(65);
        
        frontServo.write(frontLeftUp);
        delay(125);

        frontServo.write(centerPos);
        delay(65);
    digitalWrite(Pin, HIGH);
        
   }
    

void moveBackward()  

   {
        digitalWrite(Pin, LOW);
    frontServo.write(frontRightUp);
        delay(125);
        
    frontServo.write(centerPos);
        delay(65);
    
    frontServo.write(frontLeftUp);
        delay(125);
    
    frontServo.write(centerPos);
        delay(65);
    digitalWrite(Pin, HIGH);
   }


void moveBackRight()  
   
   {
        digitalWrite(Pin, LOW);
        frontServo.write(frontRightUp);
        delay(125);
    
    frontServo.write(centerPos);
        delay(65);
    
    frontServo.write(frontLeftUp+9);
        delay(125);
    
    frontServo.write(centerPos);
        delay(65);
    digitalWrite(Pin, HIGH);
   }

void moveBackLeft()  
   
   {
        digitalWrite(Pin, LOW);
        frontServo.write(frontRightUp);
        delay(125);
    
    frontServo.write(centerPos);
        delay(65);
    
    frontServo.write(frontLeftUp-9);
        delay(125);
    
    frontServo.write(centerPos);
        delay(65);
    digitalWrite(Pin, HIGH);
   }


void moveTurnLeft()  
   
   {
        digitalWrite(Pin, LOW);
        frontServo.write(frontRightUp-9);
        delay(125);
    
    frontServo.write(centerPos-9);
        delay(65);
        
    frontServo.write(frontLeftUp+9);
        delay(125);
        
    frontServo.write(centerPos-9);
        delay(65);
    digitalWrite(Pin, HIGH);
   }


void moveTurnRight()

   {
        digitalWrite(Pin, LOW);
    frontServo.write(frontRightUp+9);
        delay(125);
    
    frontServo.write(centerPos+9);
        delay(65);
        
    frontServo.write(frontLeftUp-9);
        delay(125);
        
    frontServo.write(centerPos+9);
        delay(65);
    digitalWrite(Pin, HIGH);
   }
void startPatrol()
   {
        digitalWrite(Pin, LOW);
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
  digitalWrite(Pin, HIGH);
}


void setup()
   
   {
    frontServo.attach(2);
    pinMode (Pin, OUTPUT);
    digitalWrite (Pin, HIGH);
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
