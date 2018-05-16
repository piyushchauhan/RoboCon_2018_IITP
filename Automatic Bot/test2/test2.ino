#include <Mechanum.h>
#include <driveMotion.h>

int pwm[4] = {2, 3, 5, 4};
int dir[4] = {23, 27, 37, 33};
int brk[4] = {25, 29, 35, 31};
//Mechanumdrive bot=Mechanumdrive();
driveMotion bot=driveMotion();


void setup(){
  
  bot.init(pwm,dir,brk);
  for(int i=1;i<=8;++i)
  {
    pinMode(i,INPUT);
  }
}
void loop()
{
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
}
