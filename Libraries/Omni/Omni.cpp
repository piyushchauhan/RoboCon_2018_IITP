#include "Omni.h"
#include "Arduino.h"

void Omni::initpins(int pwmpin , int dirpin , int brkpin) {
	this->PWM = pwmpin;
	this->DIR = dirpin;
	this->BRK = brkpin;
	pinMode(PWM, OUTPUT);
	pinMode(DIR, OUTPUT);
	pinMode(BRK, OUTPUT);
}
void Omni::forward()
{
	digitalWrite(PWM, HIGH);
	digitalWrite(DIR, HIGH);
	digitalWrite(BRK, LOW);
}
void Omni::stopped()
{
	digitalWrite(PWM, LOW);
	digitalWrite(DIR, HIGH);
	digitalWrite(BRK, HIGH);
}
void Omni::backward()
{
	digitalWrite(PWM, HIGH);
	digitalWrite(DIR, LOW);
	digitalWrite(BRK, LOW);
}



