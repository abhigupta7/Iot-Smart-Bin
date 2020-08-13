#include <Servo.h>
#define moisSensorPin A0// humidity sensor attatched to analog pin 0 
float moissensorvalue = 0;
float metalDetected;
int monitoring;
int metalDetection=1; //inductive meatallic sensor attatched to analog pin 1
Servo myservo1; 
Servo myservo2;
Servo myservo3;   
void setup() 
{
   Serial.begin(9600);
   myservo1.attach(7); //wet comp.
   myservo2.attach(8); //metal comp.
   myservo1.attach(9); //dry comp.
}
void loop() 
{
 monitoring = analogRead(metalDetection);
 if (monitoring > 550)
 {
   myservo2.write(90);
   delay(10000);
   myservo2.write(0);
 }
 else
 {
  for (int i = 0; i <= 50; i++) 
  { 
     moissensorvalue = moissensorvalue + analogRead(moisSensorPin); 
    delay(1); 
  } 
  moissensorvalue = moissensorvalue/50.0;
   if (moissensorvalue>500)
    {
      myservo1.write(90); // sets the servo position according to the scaled value
      delay(10000);
      myservo1.write(0);
    }
  else
    {
      delay(5000);
      myservo3.write(90);
      delay(10000);
      myservo3.write(0);
    }
  }
}
