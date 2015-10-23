#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
//  sensor_t sensor;
 // mag.getSensor(&sensor);
int flag=1;
int flag2=1;
int facing=0;


#define a2 22
#define a1 23
#define b1 24
#define b2 25

#define c1 52
#define c2 53
#define dd2 51
#define dd1 50


#define trigPin4 34
#define echoPin4 35
#define trigPin3 30
#define echoPin3 31
#define trigPin2 32
#define echoPin2 33
#define trigPin1 36
#define echoPin1 37

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


int n;
int s;
int e;
int w;

#define min_d 20
#define min_side 25
#define derr 30

#define error 5
int time=1490;

// the setup routine runs once when you press reset:
void setup() {   

  // set up the LCD's number of columns and rows: 
  lcd.begin(32, 4);
  // Print a message to the LCD.
  //lcd.print("GROUP 18");

   Serial.begin (9600);  
  // initialize the digital pin as an output.
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(dd1, OUTPUT);
  pinMode(dd2, OUTPUT);
 
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  mag.begin();
  n=direction();
  s=n-180;
  e=n+90;
  w=n-90;
  if(s<0)
  s=s+360;
  if(w<0)
  w=w+360;
  if(e>360)
  e=e-360;
  
  /*
  s=direction();
  n=s-180;
  w=s+90;
  e=s-90;
  if(n<0)
  n=n+360;
  if(w>360)
  w=w-360;
  if(e<0)
  e=e+360;
  */
/* n=290;
  e=355;
  s=96;
  w=208;
  */
  /*
  int temper=e;
  e=w;
  w=temper;
  n=118;  
  e=70;
  s=34;
  w=326;*/
  Serial.println(n);
  Serial.println(s);
  Serial.println(e);
  Serial.println(w);

}

 void straight()
  {
   digitalWrite(a1,HIGH);
   digitalWrite(a2, LOW);
   digitalWrite(b1, HIGH);
   digitalWrite(b2, LOW);
   digitalWrite(c1, HIGH);
   digitalWrite(c2, LOW);
   digitalWrite(dd1, HIGH);
   digitalWrite(dd2, LOW);
   
  }
  
 void right()
  {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(c1, HIGH);
  digitalWrite(c2, LOW);
  digitalWrite(dd1, HIGH);
  digitalWrite(dd2, LOW);
 
 }
 void left()
  {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);

  digitalWrite(c1, LOW);
  digitalWrite(c2, HIGH);
  digitalWrite(dd1, LOW);
  digitalWrite(dd2, HIGH);
 }
 void back()
  {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(c1, LOW);
  digitalWrite(c2, HIGH);
  digitalWrite(dd1, LOW);
  digitalWrite(dd2, HIGH);
 
 
 }
 void stopr()
  {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  digitalWrite(dd1, LOW);
  digitalWrite(dd2, LOW);
  
 }


long distance4()
{
     long duration, distance;
  digitalWrite(trigPin4, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin4, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin4, LOW);
  duration = pulseIn(echoPin4, HIGH);
  distance = (duration/2) / 29.1;
    return distance;
  
}


long distance3()
{
     long duration, distance;
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  distance = (duration/2) / 29.1;
    return distance;
  
}



long distance2()
{
     long duration, distance;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance = (duration/2) / 29.1;
    return distance;
  
}


long distance1()
{
     long duration, distance;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration/2) / 29.1;
    return distance;
  
}





int wallright()
{
  if(distance4()<min_side)
  return 1;
  else
  return 0;
}
int wallleft()
{
  if(distance1()<min_side)
  return 1;
  else
  return 0;
}
int wallstraight1()
{
  if(distance2()<min_d)
  return 1;
  else
  return 0;
}
int wallstraight2()
{
  if(distance3()<min_d)
  return 1;
  else
  return 0;
}


float direction()
{
  sensors_event_t event; 
  mag.getEvent(&event);
 
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  if(heading < 0)
    heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI; 
  delay(30);
  return headingDegrees;
   
}

void align_north()
{
      float d1,d2;
      d1=direction();
      if((n-d1)>error)
      {
        right();
      }   
      else if((n-d1) < -error)
      left();
      while(!(d1>(n-error) && d1<(n+error)))
        {
             delay(2);  // 30
             d1=direction();
        }
        stopr();
        d1=direction();
        if(!(d1>(n-error) && d1<(n+error)))
            align_north();
     
   Serial.println("Facing North");
}


void align_south()
{
      float d1,d2;
      d1=direction();
      if((s-d1)>error)
      {
        right();
      }   
      else if((s-d1) < -error)
      left();
      while(!(d1>(s-error) && d1<(s+error)))
        {
             delay(2);
             d1=direction();
        }
        stopr();
        d1=direction();
        if(!(d1>(s-error) && d1<(s+error)))
            align_south();
        //straight(); 
   Serial.println("Facing South");
}


void ta_right()
{
        Serial.println("TA Right");
        float d1,d2; 
        d1=direction();
        Serial.println(d1);
        right();
        while(!(d1>(e-error) && d1<(e+error)))
        {
              delay(2);  //30
              d1=direction();
              Serial.println(d1);
        }
         stopr();
         lcd_dis();
         delay(300);
        
 
      Serial.println("Facing East");
      straight(); 
      Serial.println("Straight");
      delay(600);  // 300
      Serial.println("Moved straight");
   
       right();
        while( !(d1>(s-error) && d1<(s+error)))
        {
             delay(2);
             d1=direction();
             Serial.println(d1);
        
        }
  Serial.println("Facing South");
     
        Serial.println("Straight");
     
         stopr();
         lcd_dis();
         delay(100);
     
         align_south();
       stopr();
      delay(100);
        straight(); 
     

}










void ta_right1()
{
        right();
       delay(time);
         stopr();
         delay(1000);
        straight();
        delay(600);
        stopr();
        delay(1000);
        right();
       delay(time);
         stopr();

         delay(1000);
     //   straight();
}



void ta_left2()
{
        left();
       delay(time);
         stopr();
         delay(1000);
        straight();
        delay(600);
        stopr();
        delay(1000);
        left();
       delay(time);
         stopr();
         delay(1000);
        straight();
}


void ta_right2()
{
   float d1;
 
       right();
       delay(time);
         stopr();
         delay(1000);
        straight();
        delay(600);
        stopr();
        delay(1000);
        right();
        d1=direction();
        while(!(d1>(s-error) && d1<(s+error)))
        {
             delay(2);
             d1=direction();
        }
      Serial.println("Facing North");
             
     stopr();
         lcd_dis();
         delay(1000);
     
         align_south();
       stopr();
      delay(100);
        straight(); 
     
}



void ta_left1()
{
   float d1;
 
       left();
       delay(time);
         stopr();
         delay(1000);
        straight();
        delay(600);
        stopr();
        delay(1000);
        left();
        d1=direction();
        while(!(d1>(n-error) && d1<(n+error)))
        {
             delay(2);
             d1=direction();
        }
      Serial.println("Facing North");
             
     stopr();
         lcd_dis();
         delay(1000);
     
         align_north();
       stopr();
      delay(100);
    //    straight(); 
     
}






void ta_left()
{
        Serial.println("TA Left");
        float d1,d2; 
        d1=direction();
        left();
        while( !(d1>(e-error) && d1<(e+error)))
        {
             delay(2);
             d1=direction();
        }
        
      Serial.println("Facing East");
      Serial.println("Straight");
            
       stopr();
         lcd_dis();
         delay(300);
        straight(); 
        delay(600);
          
      //delay(300);
      Serial.println("Moved straight");
      left();
        while(!(d1>(n-error) && d1<(n+error)))
        {
             delay(2);
             d1=direction();
        }
      Serial.println("Facing North");
             
     stopr();
         lcd_dis();
         delay(100);
     
         align_north();
       stopr();
      delay(100);
        straight(); 
     
}

void lcd_dis()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print("D1 : ");
  lcd.print(distance1());
  lcd.print("  D2 : ");
  lcd.print(distance2());
  lcd.setCursor(0, 1);
  lcd.print("D3 : ");
  lcd.print(distance3());
  lcd.print("  D4 : ");
  lcd.print(distance4());
  lcd.setCursor(0,2);
  lcd.print("Flag 1 ");
  lcd.print(flag);
  
  lcd.setCursor(0,3);
  lcd.print("Flag 2 ");
  lcd.print(flag2);
lcd.print(" Dir ");
  lcd.print(direction());
    
  
}


  /*
 if(cnt==-1)
{
float d1=direction();
right();
delay(1000);
d1=direction();
  while(!(d1>(n-error) && d1<(n+error)))
   {
           delay(600);  //30
            d1=direction();
 //           Serial.println(d1);
           time++;
    }
    
 stopr();
time=time*600+1000;
time=time/4;

} */
void wallfollow()
{
  
   lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Wall follow");
     straight();
      while(wallleft() && !(wallstraight1() || wallstraight2()))
      {
        delay(40);
      }
      if(wallstraight1() || wallstraight2())
       {
         ta_right1();
         facing=1;
       }
       else if(!wallleft())
       { 
      lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Following Wall");
         
         stopr();
        delay(1000);
         straight(); 
         delay(1000);
          left();
          delay(time);
           stopr();
           delay(1000);
           straight();
           delay(500);
           while(wallleft())
           {
            delay(50); 
           } 
           right();
 
           delay(time);
           stopr();
           delay(1000);
       }
        else
        {
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("No condition fullfilled");
     
              stopr();
              delay(2000);
        }
}
  
int cnt=-1;
// the loop routine runs over and over again forever:
void loop() {

  
 straight();

  cnt++;
cnt=cnt%10;
if(cnt==0)
lcd_dis();
//int nt=n;
//if()
//Serial.print(-20 % 360);
/*  int dt=direction();
  if(n>360-derr && n < 360 && dt >0 && dt<derr)
        dt=dt+360;
  
  if(dt>360-derr && dt < 360 && n >0 && n<derr)
        dt=dt-360;
  */
  
//   if((wallstraight1() || wallstraight2()) && dt< n+derr && dt > n-derr)
  if((wallstraight1() || wallstraight2()) && facing==0)
     {
    
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("North Wall");
     
     /*if(wallright())
     {
      right();
      delay(2*time);
      stopr();
      delay(1000);
      straight();
     }*/
     //else
     //{
     if(flag2==1)
        {
          stopr();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("END");
           while(1){delay(1000);}
        }
   
   
   
       ta_right1();
       lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Moved right");
     delay(500);
     facing = 1;
    
    if(wallleft())
   {
        flag=1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Wall left");
     
   }
     else
        flag=0;
        straight();
     //}  
   }

  if((wallstraight1() && !wallstraight2()) && facing==1)
     {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Obstacle bypass");
           right();
           delay(time);
           stopr();
           delay(1000);
           straight();
           delay(500);
           stopr();
           delay(500);
           left();
           delay(time);
           stopr();
           delay(1000);
           straight();
         
   } 

  else if((wallstraight1() || wallstraight2()) && facing==1)
     {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("South Wall");
    
         if(flag==1)
          {
             stopr();
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("END");
            while(1){delay(1000);}
          }
           
         ta_left1();
         facing = 0;
         lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Turned left");
    
         if(wallright())
         {
            flag2=1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Wall Right");
     
         } 
       else
          flag2=0;
       
 
   } 
     
 
 
 
 
 
 
   if(!wallleft())
        flag=0; 
     
   if(!wallright())
        flag2=0; 
 
 // addition for sqrue    
   if(wallleft() && (facing == 0))
   {
         wallfollow();      
   }    
  /*   if(facing==0)
     align_north();
     if(facing ==1)
     align_south();
     */

delay(50);
}
