#include "Arduino.h"
#include "Omni.h"
Omni::Omni(int pwmpin , int dirpin , int brkpin)
{
	this->PWM=pwmpin;
	this->DIR=dirpin;
	this->BRK=brkpin;
	pinMode(PWM , OUTPUT);
	pinMode(DIR , OUTPUT);
	pinMode(BRK , OUTPUT);
}
void Omni::forward()
{
	digitalWrite(PWM,HIGH);
	digitalWrite(DIR,HIGH);
	digitalWrite(BRK,LOW);
}
void Omni::stopped()
{
	digitalWrite(PWM,LOW);
	digitalWrite(DIR,LOW);
	digitalWrite(BRK,LOW);
}
void Omni::backward()
{
	digitalWrite(PWM,HIGH);
	digitalWrite(DIR,LOW);
	digitalWrite(BRK,LOW);	
}



