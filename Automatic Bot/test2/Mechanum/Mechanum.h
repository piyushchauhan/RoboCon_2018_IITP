#ifndef Mechanum_h
#define Mechanum_h


class Mechanum
{
public:
  void initpins(int pwmpin , int dirpin , int brkpin);
  void forward();
  void backward();
  void stopped();

protected:
  int PWM , DIR , BRK;
};

#endif
