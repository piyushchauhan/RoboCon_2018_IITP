#include "Omni.h"
#include "Arduino.h"
#include "Drive.h"
Drive::Drive() : 
	Omni() {motor1;motor2,motor3;
	
}
void Drive::init(int pwm[], int dir[], int brk[])
{

	motor1.initpins(pwm[0], dir[0], brk[0]);
	motor2.initpins(pwm[1], dir[1], brk[1]);
	motor3.initpins(pwm[2], dir[2], brk[2]);
}
void Drive::moveforward()
{
	this->motor1.stopped();
	this->motor2.forward();
	this->motor3.forward();
}
void Drive::movebackward()
{
	this->motor1.stopped();
	this->motor2.backward();
	this->motor3.backward();
}
void Drive::moveleft()
{
	this->motor1.backward();
	this->motor2.backward();
	this->motor3.forward();
}
void Drive::moveright()
{
	this->motor1.forward();
	this->motor2.forward();
	this->motor3.backward();
}
