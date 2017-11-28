#ifndef Omni_h
#define Omni_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
class Omni
{
public:
  //Omni();
  Omni(float a, float b);
  void setMotion(int vx, int vy, int w);
  int getw1();
  int getw2();
  int getw3();
  int getw4();
private:
  int Max(int a, int b, int c, int d);
  int w1, w2, w3, w4,W1,W2,W3,W4,wmax;
  float d, R;
};
extern Omni omni;
#endif
