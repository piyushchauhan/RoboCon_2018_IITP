#ifndef Drive_h
#define Drive_h

#include "Omni.h"

class Drive: public Omni
{
private:
  int pwm[3];
  int dir[3];
  int brk[3];
  Omni motor1;
  Omni motor2;
  Omni motor3;


public:
  Drive();
  void init(int pwm[], int dir[], int brk[]);
  void moveforward();
  void movebackward();
  void moveright();
  void moveleft();
  void stopall();

};

#endif
