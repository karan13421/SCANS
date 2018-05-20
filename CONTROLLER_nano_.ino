#include<SoftwareSerial.h>

const int trig1=5;
const int echo1=6;
const int trig2=3;
const int echo2=4;

const int blueTx=11;
const int blueRx=10;

SoftwareSerial bluetooth(blueTx,blueRx);

int detect1,detect2,last1,last2;
int count=0;

unsigned int select;

void setup() 
{
pinMode(trig1,OUTPUT);
pinMode(echo1,INPUT);
pinMode(trig2,OUTPUT);
pinMode(echo2,INPUT);

last1=0;
last2=0;
Serial.begin(9600);
bluetooth.begin(9600);
}

void loop() {
  if(bluetooth.available()>0)
  {
    select=bluetooth.read();                                        
    if(select==111)
    {
      switcher();
      Serial.write(161);
    }
    if(select==222)
    {
      alertSystem();
    }

    if(select==233)
    {
      AIswitch(select);// Notifying System
    }

    if(select==244)
    {
      AIswitch(select);// Counting mode
    }

  }

}

void switcher()
{
  int device;
  while(1)
  { 
    if(bluetooth.available()>0){
     device=bluetooth.read();
     if(device==101)
     {
      Serial.write(device);
     }
     else
     if(device==100)
     {
     Serial.write(device);
     }
     
     if(device==121)
     {
    Serial.write(device);
     }
     else
     if(device==120)
    Serial.write(device);

     if(device==131)
     {
     Serial.write(device);
     }
     else
     if(device==130)
     Serial.write(device);

     if(device==141)
     {
     Serial.write(device);
     }
     else
     if(device==140)
    Serial.write(device);

     if(device==151)
     {
       Serial.write(161);
       AIswitch(device);
     }

     if(device==161)
     {
      Serial.write(device);
       AIswitch(device);
     }
     
     if(device==99)
     {
       //Serial.print("   GET OFF  ");
      Serial.write(161);
       break;
     }
     
    }
  }
}


void AIswitch(int FUNC)
{
 int look=0; //for Counting mode
 while(1)
 {
    
    detect1=calDetect1();
    detect2=calDetect2();
    //Serial.print("  Sensor");
    //Serial.print(detect1);
    //Serial.print(" ");
    //Serial.print(detect2);
 if((detect1<60)&&(detect2>90))
 {
  while(1)
  {  
     
    if((calDetect2()<60)&&(detect2>90)&&(calDetect1()>60))
    {
      
      count++;
      delay(3);
      break;
    }
    else
    {
      last1++;
      
      if(last1>180)
      { 
        last1=0;
       
      break;
      }
    }
  }
 }

 if((detect2<60)&&(detect1>90))
 {
  while(1)
  {
    
    if((calDetect1()<60)&&(detect1>90)&&(calDetect2()>60))
    {
      
      count--;
     delay(3);
      break;
    }
    else
    {
      last2++;
      
      if(last2>180)
      {
        last2=0;
    
      break;
      }
    }
  }
 }  
     // Serial.print(" Count");
     // Serial.print(count);
    
    if(FUNC==151)
    deviceController(&count);

    if(FUNC==161)
    deviceController2(&count);

    if(FUNC==233)
    messageCon(&count);

    //count mode is with in AImode********
    if(FUNC==244)
    {
      if(look!=count)
      {
      look=count;
      bluetooth.write(look);  
      }  
    }     
   
    
    if(bluetooth.available()>0)
    {
      int check=0;
      check=bluetooth.read();

     
      if(check==99)
      {
        Serial.write(161);
       count=0;
       break;
      }
    }

 }
}



void deviceController(int *device)
{
 
  if(*device>0)
  {
    Serial.write(151);  
  }

  if(*device<=0)
  {
       Serial.write(161);
       *device=0;
  }
}


void deviceController2(int *device)
{

    if(*device==0)
    {
     Serial.write(161);
    }
    
    if(*device==1)
    {
    //digitalWrite(device4,LOW);
    //digitalWrite(device3,LOW);
    //digitalWrite(device2,LOW);
    //digitalWrite(device1,HIGH);
     Serial.write(*device);
    }
    
    if(*device==2)
    {
   // digitalWrite(device4,LOW);
   // digitalWrite(device3,LOW);
   // digitalWrite(device2,HIGH);
    //digitalWrite(device1,HIGH);
    Serial.write(*device);
    }

    if(*device==3)
    {
   // digitalWrite(device4,LOW);
   // digitalWrite(device3,HIGH);
   // digitalWrite(device2,HIGH);
   // digitalWrite(device1,HIGH);
    Serial.write(*device);
    }
    
    if(*device==4)
    {
   // digitalWrite(device4,HIGH);
   // digitalWrite(device3,HIGH);
   // digitalWrite(device2,HIGH);
   // digitalWrite(device1,HIGH);
    Serial.write(*device);
    }
    
    if(*device>4)
    {
     *device=4;
    }
    else
     if(*device<0)
     *device=0;
 }

int calDetect1()
{
  int distance1;
  float duration1;
  digitalWrite(trig1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  duration1=pulseIn(echo1,HIGH);
  distance1=(int)duration1*0.034/2;
  return distance1;
}

int calDetect2()
{
  int distance2;
  float duration2;
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
  duration2=pulseIn(echo2,HIGH);
  distance2=(int)duration2*0.034/2;
  return distance2;
}

void alertSystem()
{
  int look1=0,look2=0;
  int call=1;
  while(1)
  {
    if((calDetect1()<70)||(calDetect2()<70))
    {
      
       bluetooth.print("abcd");
       bluetooth.print("abcd");
       look1=calDetect1();
       look2=calDetect2();
      while((look1<70)||(look2<70))
      {
        if(bluetooth.available()>0)
         {
          call=bluetooth.read();
            if(call==99)
             break;
         }
          delay(1);
          look1=calDetect1();
          look2=calDetect2();
      }
    }
    
    if((calDetect1()>70)||(calDetect2()>70))
    {
      //Serial.print("wwwell");
      
      bluetooth.print("jklm");
      bluetooth.print("jklm");
      
      while((calDetect1()>=70)||(calDetect2()>=70))
      {
        if(bluetooth.available()>0)
         {
          call=bluetooth.read();
            if(call==99)
             break;
          }
          delay(1);
      }
    }
    
    
      if(call==99)
      {
      break;
      }
    
    
  }
}

void messageCon(int *guest)//do not have break or return in aiswitch*************
{
  //Serial.print("in message mode");
  if(*guest>=1)
  {
    //Serial.print(" MessageIN ");
    bluetooth.print("abcd");
    bluetooth.print("abcd");
    delay(100);
    *guest=0;
  }

  if(*guest<0)
  {
    bluetooth.print("krnm");
   bluetooth.print("krnm");
   delay(100);
    *guest=0;
  }
}






