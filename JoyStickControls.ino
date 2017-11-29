#include <Shield_PS2.h>
#include "Omni.h"

PS2 ps2=PS2();                    //PS2 class object: ps2
Omni omni(37.5,5);

//PS2 status
int Left_button, Down_button, Right_button, Up_button, Start_button, Right_Joystick_button, Left_Joystick_button, Select_button;
int Square_button, Cross_button, Circle_button, Triangle_button, R1_button, L1_button, R2_button, L2_button;
int Right_Joystick_x, Right_Joystick_y, Left_Joystick_x, Left_Joystick_y;

int M1A= 5,M1B = 4,M2A = 7,M2B = 6,M3A = 9,M3B = 8,M4A = 3,M4B = 2;
int vx,vy;

//characters to display on LCD

void setup()
{
   Serial.begin(57600);

   //PS2 Setup
   ps2.init(57600, 10, 11);   //initialize the main board to use desired (baudrate, rx, tx)
   ps2.reset(1);              //call to reset Shield-PS2
   ps2.reset(0);
   Serial.println("PS2 Remote_Cytron Shield");
   Serial.println("Press Start");

   //Motor Pins
   pinMode(M1A, OUTPUT);
   pinMode(M1B, OUTPUT);
   pinMode(M2A, OUTPUT);
   pinMode(M2B, OUTPUT);
   pinMode(M3A, OUTPUT);
   pinMode(M3B, OUTPUT);
   pinMode(M4A, OUTPUT);
   pinMode(M4B, OUTPUT);

   while((ps2.getval(p_start)));  //Wait untill start button on PS2 to be pressed

   Serial.println("Good");

   delay(2000);
}

void loop()
{
  if(ps2.getall()==true)      //get all buttons and joystick status
  {
    getdata();

    if((Left_Joystick_y > 130)||(Left_Joystick_y < 125))
      vx = Left_Joystick_y;
    else
      vx = 128;

    if((Right_Joystick_x > 130)||(Right_Joystick_x < 125))
      vy = Right_Joystick_x;
    else
      vy = 128 ;

    move(vx, vy);
  }
  else{//not valid packet received
   Serial.println("no valid packet received");
  }
  delay(100);
}

//Simple function to print 3 digit decimal
int p_dec(char val){
  byte data=byte(val);
  return data;
}

void getdata(){
  //Group 1
  Left_button = (ps2.ps_data[0])&128;
  if(Left_button == 0)
    Serial.println("Left_button");

  Down_button = (ps2.ps_data[0])&64;
  if(Down_button == 0)
    Serial.println("Down_button");

  Right_button = (ps2.ps_data[0])&32;
  if(Right_button == 0)
    Serial.println("Right_button");

  Up_button = (ps2.ps_data[0])&16;
  if(Up_button == 0)
    Serial.println("Up_button");

  Start_button = (ps2.ps_data[0])&8;
  if(Start_button == 0)
    Serial.println("Start_button");

  Right_Joystick_button = (ps2.ps_data[0])&4;
  if(Right_Joystick_button == 0)
    Serial.println("Right_Joystick_button");

  Left_Joystick_button = (ps2.ps_data[0])&2;
  if(Left_Joystick_button == 0)
    Serial.println("Left_Joystick_button");

  Select_button = (ps2.ps_data[0])&1;
  if(Select_button == 0)
    Serial.println("Select_button");


  //Group 2
  Square_button = (ps2.ps_data[1])&128;
  if(Square_button == 0)
    Serial.println("Square_button");

  Cross_button = (ps2.ps_data[1])&64;
  if(Cross_button == 0)
    Serial.println("Cross_button");

  Circle_button = (ps2.ps_data[1])&32;
  if(Circle_button == 0)
    Serial.println("Circle_button");

  Triangle_button = (ps2.ps_data[1])&16;
  if(Triangle_button == 0)
    Serial.println("Triangle_button");

  R1_button = (ps2.ps_data[1])&8;
  if(R1_button == 0)
    Serial.println("R1_button");

  L1_button = (ps2.ps_data[1])&4;
  if(L1_button == 0)
    Serial.println("L1_button");

  R2_button = (ps2.ps_data[1])&2;
  if(R2_button == 0)
    Serial.println("R2_button");

  L2_button = (ps2.ps_data[1])&1;
  if(L2_button == 0)
    Serial.println("L2_button");

  //both joysticks values on each axes.
  Right_Joystick_x = p_dec(ps2.ps_data[2]);
  Right_Joystick_y = p_dec(ps2.ps_data[3]);
  Left_Joystick_x = p_dec(ps2.ps_data[4]);
  Left_Joystick_y = p_dec(ps2.ps_data[5]);
}

void printjoystickdata(){
   if((Right_Joystick_x > 130)||(Right_Joystick_x < 125)){
     Serial.print("Right_Joystick_x = ");
     Serial.println(Right_Joystick_x);
   }

   if((Right_Joystick_y > 130)||(Right_Joystick_y < 125)){
     Serial.print("Right_Joystick_y = ");
     Serial.println(Right_Joystick_y);
   }

   if((Left_Joystick_x > 130)||(Left_Joystick_x < 125)){
     Serial.print("Left_Joystick_x = ");
     Serial.println(Left_Joystick_x);
   }

   if((Left_Joystick_y > 130)||(Left_Joystick_y < 125)){
     Serial.print("Left_Joystick_y = ");
     Serial.println(Left_Joystick_y);
   }
}

void move(int x,int y){
  x-=128; y-=128;
  omni.setMotion(x,y,0);
  int a = omni.getw1();
  int b = omni.getw2();
  int c = omni.getw3();
  int d = omni.getw4();
  motor(a, b, c, d);
}

void motor(int a,int b, int c, int d){
  a = map(a, -25, 25, -255, 255);
  b = map(b, -25, 25, -255, 255);
  c = map(c, -25, 25, -255, 255);
  d = map(d, -25, 25, -255, 255);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  Serial.println("");
  drive(a, M1A, M1B);
  drive(b, M2A, M2B);
  drive(c, M3A, M3B);
  drive(d, M4A, M4B);
}

void drive(int a, int MA, int MB){
  if(a==0){
    digitalWrite(MA, LOW);
    digitalWrite(MB, LOW);
  }
  else if(a>0){
    analogWrite(MA, a);
    digitalWrite(MB, LOW);
  }
  else if(a<0){
    digitalWrite(MA, LOW);
    analogWrite(MB, -a);
  }
}
