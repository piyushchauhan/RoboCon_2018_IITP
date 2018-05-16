#ifndef Omni_h
#define Omni_h


class Omni
{
  public:
    Omni(int , int , int );
    void forward();
    void backward();
    void stopped();
  
  protected:
    int PWM , DIR , BRK;
};

#endif
