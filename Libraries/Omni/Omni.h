#ifndef Omni_h
#define Omni_h


class Omni
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
