#include "Mechanum.h"
#include "Arduino.h"
#include "Drive2.h"
Drive2::Drive2() : 
  Mechanum() {motor1;motor2;motor3;
  
}
void Drive2::init(int pwm[], int dir[], int brk[])
{

  motor1.initpins(pwm[0], dir[0], brk[0]);
  motor2.initpins(pwm[1], dir[1], brk[1]);
  motor3.initpins(pwm[2], dir[2], brk[2]);
  motor4.initpins(pwm[3], dir[3], brk[3]);
}
void Drive2::moveforward()
{
  this->motor1.forward();
this->motor2.forward();
this->motor3.forward();
this->motor4.forward();
}
void Drive2::movebackward()
{
  this->motor1.backward();
this->motor2.backward();
this->motor3.backward();
this->motor4.backward();
}
void Drive2::moveleft()
{
  this->motor1.backward();
this->motor2.forward();
this->motor3.backward();
this->motor4.forward();
}
void Drive2::moveright()
{
  this->motor1.forward();
this->motor2.backward();
this->motor3.forward();
this->motor4.backward();;
}
void Drive2::mstop()
{
  
this->motor1.stopped();
this->motor2.stopped();
this->motor3.stopped();
this->motor4.stopped();

}

