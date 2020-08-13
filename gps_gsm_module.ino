#include <SoftwareSerial.h>
#include <TinyGPS.h>
#define trigger  3
#define echo     4
int time_;
float distance, dist_limit = 20.00;//cms
int buzz = 13;
int state = 0;
const int pin = 9;
float gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);
  pinMode(buzz, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(buzz, LOW); 
}
void loop()
{
  int c=ultrasonic_sensor();
  if (c==1)
  {
    digitalWrite(buzz,HIGH);
  if (Serial.available()>0)
    SendMessage();
  }
  else
  {
  digitalWrite(buzz,LOW);
  }
}
 void SendMessage()
  {
    while (sgps.available())
      {
      int c = sgps.read();
      if (gps.encode(c))
        {
          gps.f_get_position(&gpslat, &gpslon);
        }
      }
      
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      sgsm.print("AT+CMGS=\"+ZZXXXXXXXXXX\"\r");
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("Latitude :");
      sgsm.println(gpslat, 6);
      sgsm.print("Longitude:");
      sgsm.println(gpslon, 6);
      delay(1000);
      sgsm.write(0x1A);
      delay(1000);
   }
   int ultrasonic_sensor()
{
  digitalWrite(trigger, HIGH);
  delay(1000);
  digitalWrite(trigger, LOW);
  time_ = pulseIn(echo,HIGH);//calculate rebound time of ultrasonic waves
  distance = time_*0.01725;
  if (distance <= dist_limit)
    return 1;
  else
    return 0;
}
