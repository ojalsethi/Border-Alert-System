#include <LiquidCrystal.h>
#define  buzzer 8
#define m1_1 7
#define m1_2 4
#define m2_1 6
#define m2_2 5
#define rled 3
#define gled 2        //45678
LiquidCrystal lcd(A0,A1,A2,A3,A4, A5);
int i; char l1,l2; float n1,n2,s1,s2,s1_max,s1_min,s2_max,s2_min;
char c[4]="1.3"; int loc=0; int set=0; int zone=0,w=0;
void setup()
{ lcd.begin(16,2);
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(buzzer,OUTPUT);
   pinMode(13,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.print("Hello");
}
char x; char location[25],lon[11],lat[10];
void loop() 
{
       gps();
                if(loc==1)
                 {
                  if(digitalRead(13)==0)
                   {
                     s1=n1;
                     s2=n2;
                     lcd.clear();
                     lcd.print("location set");
                     delay(2000);
                     lcd.clear();
                     lcd.print("lat=");lcd.print(s1,6); lcd.print(l1);
                     lcd.setCursor(0,1);
                     lcd.print("lon=");lcd.print(s2,6); lcd.print(l2);
                     delay(5000);
                     digitalWrite(gled,HIGH);
                     digitalWrite(rled,LOW);
                     set=1;
                     s1_max=23.4000; s1_min=23.2000;
                     s2_max=77.8000; s2_min=77.5000;
                     forward();
               
                     while(digitalRead(13)==0);
                   }
                 if((n1<s1_max && n1>s1_min || n2<s2_max && n2>n2_min) && set==1)
                  {  
                    stop_();
                 
                      delay(200);
                      w=1;
                      digitalWrite(rled,HIGH);
                      digitalWrite(gled,LOW);
                      digitalWrite(buzzer,HIGH);
                      delay(500);
                      digitalWrite(buzzer,LOW);
                      delay(500);
                      lcd.clear();
                      lcd.print("DANGER ZONE");
                      back();
                      gps();      
                      delay(2000);
                     }                      
                      zone=1;
                  }
                 if((n1<s1_max && n1>s1_min) && ( n2<s2_max && n2>s2_min) && zone==1 && set==1)
                  { 
                     set=1;
                     stop_();
                     delay(200);
                     while(n1<s1_max && n1<s1_min && n2<s2_max && n2<s2_min)
                     {
                      gps(); w=0;
                      digitalWrite(rled,LOW);
                      digitalWrite(gled,HIGH);
                      digitalWrite(buzzer,LOW);
                      delay(500);
                      digitalWrite(buzzer,LOW);
                      delay(500);
                      forward();
                    
                     }
                   
                      zone=0;
                  }
    delay(2000);             
                 }
}
 void gps()
 {
  while(!Serial.available())
  { 
    if(digitalRead(13)==0)  break;
    if(w==1)
    {
         digitalWrite(rled,HIGH);
                      digitalWrite(gled,LOW);
                      digitalWrite(buzzer,HIGH);
                      delay(500);
                      digitalWrite(buzzer,LOW);
                      delay(500);
                      lcd.clear();
                      lcd.print("DANGER ZONE");
                       delay(2000);
                      lcd.clear();
                     lcd.print("lat=");lcd.print(s1_min,4); lcd.print(l1);
                     lcd.setCursor(0,1);
                     lcd.print("lon=");lcd.print(s2_min,4); lcd.print(l2);
                     delay(2000);
    }
    }
     x=Serial.read();
       if(x=='$') 
            {
          while(!Serial.available());
          x=Serial.read();
            if(x=='G')
              {
               while(!Serial.available());
               x=Serial.read();
                   if(x=='P')
                   {
                     while(!Serial.available());
                     x=Serial.read();
                     if(x=='G')
                       {
                         while(!Serial.available());
                         x=Serial.read();
                          if(x=='G')
                             {
                              while(!Serial.available());
                              x=Serial.read();
                                 if(x=='A')
                                   {
                                     int count= 0;
                                     while(count<2)
                                     {
                                       while(!Serial.available());
                                       x=Serial.read();
                                         if(x==',')
                                            count++;
  
                                      }
                             
                                for(int i=0; i<24; i++)
                                   {
                                  while(!Serial.available());
                                  location[i]=Serial.read();
                        }}}}}}
        }
        lcd.clear();
    if(location[0]==',')
     {
        lcd.clear();
        lcd.print("location not found");
        delay(100);
        loc=0;
     }
    else
      {
          for( i=0; i<9; i++)
           {
            lat[i]=location[i];
            delay(1);
           }
           lat[9]='\0';
           l1=location[10];
           n1=atof(lat);
              lcd.clear();
              lcd.print("lat=");lcd.print(n1,4); lcd.print(l1);
     
          for( i=12; i<21; i++)
            {
              lon[i-12]=location[i]; delay(1);
            }
             
              lon[i-12]='\0';
              l2=location[23];
              n2=atof(lon);
              lcd.setCursor(0,1);
              lcd.print("lon=");lcd.print(n2,4); lcd.print(l2);
              loc=1;
             } }
void forward()
{
 digitalWrite(m1_1, LOW); digitalWrite(m1_2, HIGH);
 digitalWrite(m2_1, HIGH); digitalWrite(m2_2, LOW);
}
void back()
{
 digitalWrite(m1_1, HIGH); digitalWrite(m1_2, LOW);
 digitalWrite(m2_1, LOW); digitalWrite(m2_2, HIGH); 
}
void stop_()
{
 digitalWrite(m1_1, LOW); digitalWrite(m1_2, LOW);
 digitalWrite(m2_1, LOW); digitalWrite(m2_2, LOW);
}
