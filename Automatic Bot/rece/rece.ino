/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*
* by Dejan Nedelkovski, www.HowToMechatronics.com
*
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int motor_dir = 3;
int motor_pwm = 4;
// Receiver on MEGA
void setup() {
  Serial.begin(115200);
  delay(50);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(motor_dir, OUTPUT);
  pinMode(motor_pwm, OUTPUT);
}
void loop() {
  if (radio.available()) {
    int data[3] = {};// data {(Stop/Forward/Backward, Ton,Toff)}
    radio.read(&data, sizeof(data));
    if (data[0] == 0)
      Stop(data[1], data[2]);
    else if (data[0] == 1)
      Forward(data[1], data[2]);
    else if (data[0] == 2)
      Backward(data[1], data[1]);
  }
}

void Stop(int on, int off) {
  digitalWrite(motor_dir, LOW);
  digitalWrite(motor_pwm, LOW);
  delay(on);
  delay(off);
}

void Backward(int on, int off) {
  digitalWrite(motor_dir, LOW);
  digitalWrite(motor_pwm, HIGH);
  delay(on);
  digitalWrite(motor_dir, LOW);
  digitalWrite(motor_pwm, LOW);
  delay(off);

}

void Forward(int on, int off) {
  digitalWrite(motor_dir, HIGH);
  digitalWrite(motor_pwm, HIGH);
  delay(on);
  digitalWrite(motor_dir, LOW);
  digitalWrite(motor_pwm, LOW);
  delay(off);

}
