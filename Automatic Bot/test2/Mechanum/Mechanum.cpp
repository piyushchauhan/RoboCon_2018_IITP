
#include "Mechanum.h"
#include "Arduino.h"

void Mechanum::initpins(int pwmpin , int dirpin , int brkpin) {
  this->PWM = pwmpin;
  this->DIR = dirpin;
  this->BRK = brkpin;
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(BRK, OUTPUT);
}
void Mechanum::forward()
{
  digitalWrite(PWM, HIGH);
  digitalWrite(DIR, HIGH);
  digitalWrite(BRK, LOW);
}
void Mechanum::stopped()
{
  digitalWrite(PWM, LOW);
  digitalWrite(DIR, HIGH);
  digitalWrite(BRK, LOW);
}
void Mechanum::backward()
{
  digitalWrite(PWM, HIGH);
  digitalWrite(DIR, LOW);
  digitalWrite(BRK, LOW);
}



