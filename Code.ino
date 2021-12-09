//use a softwareserial for GSM The Rx of GSM will be connected to pin 10 and Tx will be connected to pin 9
//sendsms2() has been written such that it uses software serial for GSM communication 

#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 3, TXPin = 2;
static const uint32_t gps_baudrate = 9600;
TinyGPSPlus gps;
SoftwareSerial soft(RXPin, TXPin);
//use a softwareserial for GSM 
SoftwareSerial mySerial(9, 10);
String textMessage;
float Lat, Lon;
void setup()
{
  pinMode(12,INPUT);
  pinMode(4, OUTPUT);
  soft.begin(gps_baudrate);
  //Serial.begin(19200);
  mySerial.begin(19200);
  Serial.begin(9600);

}
void loop()
{
  int key = digitalRead(12);
  while (soft.available() > 0)
  {
    gps.encode(soft.read());
    if (gps.location.isUpdated())
    {
      Lat = gps.location.lat();
      Lon = gps.location.lng();
    }
   else;
  }
  if(key==1)
  {
    digitalWrite(4,HIGH);
    sendsms2();
    digitalWrite(4,LOW);
  }
  { 
      Serial.println("Calling through GSM Modem");
// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
mySerial.println("ATDxxxxxxxxxx;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
Serial.println("Called ATDxxxxxxxxxx");
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}
}
// set the data rate for the SoftwareSerial port
void sendsms()
{
    Serial.print("AT+CMGF=1\r");
    delay(100);
    Serial.println("AT+CMGS =\"+918169489176 \"");
    delay(100);
    Serial.println("I want Help !!!Location:" + String("Lat: ") +String(Lat) + " "+String("Lon: ") + String(Lon));
    delay(100);
    Serial.println((char)26);
    delay(100);
    Serial.println();
    delay(5000);
}
void sendsms2()
{
 mySerial.println("AT+CMGF=1\r");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second 
 
 
    mySerial.println("AT+CMGS=\"+918169489176\""); // Replace x with mobile number
     delay(1000);
     mySerial.println("I AM IN DANGER,HELP!! ");// The SMS text you want to send
     delay(500);
     mySerial.println(Lat,3);// The SMS text you want to send the number denotes the decimal point till which want the floating point number 
     delay(500);
     mySerial.println(Lon,3);// The SMS text you want to send
     delay(500);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);

}

