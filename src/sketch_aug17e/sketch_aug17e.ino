  #include <Servo.h>

   Servo frontServo;
   
   int centerPos = 90;  
   int frontRightUp = 50;  
   int frontLeftUp = 130;  
   int backRightForward = 75;  
   int backLeftForward = 105;
   int walkSpeed = 60;
   int Pin = 13;
   int In = 0;

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
    digitalWrite (7, LOW);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(38400);
   }

void loop()

{
    if (Serial.available() > 0)
    {
       In = Serial.read();
       Serial.println(In);
    }
       if(In=='1')
        {
                  distanceFront=distanceCm();  
                  if (distanceFront > 1)
              {                
  
                   if (distanceFront<startAvoidanceDistance) 
            {  
                    for(int i=0; i<=8; i++) 
               {  
                      moveBackRight();
                      digitalWrite(7, HIGH);
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
       else if(In=='2')
        {
           moveForward();  
                   delay(walkSpeed);
        } 
       else if(In=='3')
        {
           moveBackward();
           delay(walkSpeed);
        }
       else if(In=='4')
        {
           moveTurnLeft();
           delay(walkSpeed);
        }
       else if(In=='5')
        {
           moveTurnRight();
           delay(walkSpeed);
        }
       else if(In=='6')
        {
           moveBackLeft();
           delay(walkSpeed);
        }
       else if(In=='7')
        {
           moveBackRight();
           delay(walkSpeed);
        }
       else if (In=='8')
        {
          startPatrol();
          delay(walkSpeed);
        }
       else 
        {
           center();
        }

 }
