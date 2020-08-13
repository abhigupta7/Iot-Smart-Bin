include <Servo.h>
Servo servo1;
int trigPin = 9;
int echoPin = 8;
long distance;
long duration;
 
void setup() 
{
servo1.attach(7); 
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);// put your setup code here, to run once:
}

void loop() 
{
  Measuredistance();
  if(distance <= 10)
  {
  servo1.write(90);
  delay(50000);
  servo1.write(0);
  }
 delay(30000);
}
void Measuredistance()
{
  digitalWrite(trigPin, LOW);
  delay(2000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*(0.034/2);
 }
