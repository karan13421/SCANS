#include<SoftwareSerial.h>

const int device1=3;
const int device2=4;
const int device3=5;
const int device4=6;

 int device=0;

void setup()
{
pinMode(device1,OUTPUT);
pinMode(device2,OUTPUT);
pinMode(device3,OUTPUT);
pinMode(device4,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
Serial1.begin(9600);
Serial.print("Start");

}

void loop()
{

  if(Serial1.available()>0)
  {
    device=Serial1.read();
    Serial.print("<");
    Serial.print(device);
    Serial.print(">");

    if(device==101)
     {
      Serial.print(" Device1ON");
      digitalWrite(device1,HIGH);
     }
     else
     if(device==100)
     {
     Serial.print("Device1OFF");
     digitalWrite(device1,LOW);
     }
     
     if(device==121)
     {
      Serial.print(" Device2ON");
      digitalWrite(device2,HIGH);
     }
     else
     if(device==120)
     digitalWrite(device2,LOW);

     if(device==131)
     {
      Serial.print(" Device3ON");
      digitalWrite(device3,HIGH);
     }
     else
     if(device==130)
     digitalWrite(device3,LOW);

     if(device==141)
     {
      Serial.print(" Device4ON");
      digitalWrite(device4,HIGH);
     }
     else
     if(device==140)
     digitalWrite(device4,LOW);

     if(device==151)
     {
       digitalWrite(device1,HIGH);
       digitalWrite(device2,HIGH);
       digitalWrite(device3,HIGH);
       digitalWrite(device4,HIGH);
       Serial.print("AIOUT");
     }

     if(device==161)
     {
       digitalWrite(device1,LOW);
       digitalWrite(device2,LOW);
       digitalWrite(device3,LOW);
       digitalWrite(device4,LOW);
       Serial.print("CountOUT");
     }
    
    if(device==1)
    {
    digitalWrite(device4,LOW);
    digitalWrite(device3,LOW);
    digitalWrite(device2,LOW);
    digitalWrite(device1,HIGH);
    }
    
    if(device==2)
    {
    digitalWrite(device4,LOW);
    digitalWrite(device3,LOW);
    digitalWrite(device2,HIGH);
    digitalWrite(device1,HIGH);
    }

    if(device==3)
    {
    digitalWrite(device4,LOW);
    digitalWrite(device3,HIGH);
    digitalWrite(device2,HIGH);
    digitalWrite(device1,HIGH);
    }
    
    if(device==4)
    {
    digitalWrite(device4,HIGH);
    digitalWrite(device3,HIGH);
    digitalWrite(device2,HIGH);
    digitalWrite(device1,HIGH);
    }


  }
  

}


