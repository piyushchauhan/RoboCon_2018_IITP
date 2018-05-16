#ifndef Drive2_h
#define Drive2_h

#include "Mechanum.h"

class Drive2: public Mechanum
{
private:
  int pwm[4];
  int dir[4];
  int brk[4];
  Mechanum motor1;
  Mechanum motor2;
  Mechanum motor3;
  Mechanum motor4;


public:
  Drive2();
  void init(int pwm[], int dir[], int brk[]);
  void moveforward();
  void movebackward();
  void moveright();
  void moveleft();
  void mstop();

};
#endif
