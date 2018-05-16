#include <Mechanum.h>
#include <driveMotion.h>

int pwm[4] = {2, 3, 5, 4};
int dir[4] = {23, 27, 37, 33};
int brk[4] = {25, 29, 35, 31};
//Mechanumdrive bot=Mechanumdrive();
driveMotion bot=driveMotion();


void setup(){
  Serial.begin(9600);
  bot.init(pwm,dir,brk);
  
  for(int i=9;i<=13;++i)
  {
    pinMode(i,INPUT);
  }
  pinMode(22, INPUT);
  /*
 pinMode(4, OUTPUT);
 pinMode(33, OUTPUT);
 pinMode(31, OUTPUT);

 */
}
int d2,d3,d4,d5,d6,d7;
void loop()
{/*
  if(digitalRead(2) && digitalRead(5))
  {
    bot.moveforward();
  }
  else if(digitalRead(1) && digitalRead(2))
   {
    bot.moveleft();
  }
 else if(digitalRead(5) && digitalRead(6))
   {
    bot.moveright();
  }
 else if(digitalRead(3) && digitalRead(4))
   {
    bot.mstop();
  }  
  */
d2 = digitalRead(11);
d3 = digitalRead(12);
d4 = digitalRead(9);
d5 = digitalRead(10);
d6 = digitalRead(22);
d7 = digitalRead(13);


Serial.println(d2);
Serial.print(d3);
Serial.print(d4);
Serial.print(d5);k
Serial.print(d6);
Serial.print(d7);
delay(100);

  /*
  bot.moveleft();
  delay(5000);
  bot.mstop();
  delay(1000);
  bot.moveright();
  delay(5000);
  bot.mstop();
  delay(1000);
  bot.movebackward();
  bot.mstop();
  delay(1000);
  
  analogWrite(4, 60);
  digitalWrite(33, HIGH);
  delay(1000);
  */

}

