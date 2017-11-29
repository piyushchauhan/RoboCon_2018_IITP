#include "DriveMatrix.h"

DriveMatrix::DriveMatrix(float a, float b, float c){
  l = a;L = b;Rw = c;
  lm = (l+L)/2; 
};

void DriveMatrix::setMotion(float vx, float vy, float w){
  w1 = (vx-vy-lm*w)/Rw;
  w2 = (vx+vy+lm*w)/Rw;
  w3 = (vx+vy-lm*w)/Rw;
  w4 = (vx-vy+lm*w)/Rw;
};

float DriveMatrix::getw1(){
  return w1;
};
float DriveMatrix::getw2(){
  return w2;
};
float DriveMatrix::getw3(){
  return w3;
};
float DriveMatrix::getw4(){
  return w4;
};

