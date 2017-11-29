#ifndef DriveMatrix_h
#define DriveMatrix_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
class DriveMatrix
{
public:
  //DriveMatrix();
  DriveMatrix(float a, float b, float c);
  void setMotion(float vx, float vy, float w);
  float getw1();
  float getw2();
  float getw3();
  float getw4();
private:
  float w1, w2, w3, w4, l, L,Rw,lm;
};
extern DriveMatrix Drive;
#endif
