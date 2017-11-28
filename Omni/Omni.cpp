#include "Omni.h"

Omni::Omni(float a, float b){
  // l = a;L = b;R = c;
  d = a;R = b;//R is radius of the wheels
};

void Omni::setMotion(int v, int vn , int w){
  w1 = (vn+d*w)/R;
  w2 = (-v+d*w)/R;
  w3 = (-vn+d*w)/R;
  w4 = (v+d*w)/R;
  wmax = Max(w1,w2,w3,w4);
  W1 = (w1/wmax)*255;
  W2 = (w2/wmax)*255;
  W3 = (w3/wmax)*255;
  W4 = (w4/wmax)*255;
};

int Omni::getw1(){
  return W1;
};
int Omni::getw2(){
  return W2;
};
int Omni::getw3(){
  return W3;
};
int Omni::getw4(){
  return W4;
};
int Omni::Max(int w1, int w2, int w3,int w4){
  
  if (abs(w1) >= abs(w2) && abs(w1) >=abs(w3) && abs(w1) >= abs(w4)){
    return w1;
  }
  else if(abs(w2) >= abs(w1) && abs(w2) >=abs(w3) && abs(w2) >= abs(w4)){
    return w2;
  }
  else if(abs(w3) >= abs(w1) && abs(w3) >=abs(w3) && abs(w3) >= abs(w4)){
    return w3;
  }
  else if(abs(w4) >= abs(w1) && abs(w4) >=abs(w2) && abs(w4) >= abs(w3)){
    return w4;
  }
};


