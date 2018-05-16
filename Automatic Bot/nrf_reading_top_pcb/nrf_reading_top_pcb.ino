/*
* Top pcb autonomous robot
*
*
* by Bhushan Deo,
*
* Library: TMRh20/RF24,
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN see proper pins
const byte address[6] = "00001";
char text[32] = "";

int sol = 3; // solenoid pin
int laserPin;
boolean ballBTW = 0;
int set90 = 0;

short int grip = 0;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(sol, OUTPUT);
}
void loop() {

  // If laser detected
  boolean val = digitalRead(laserPin);
  if (val == 1)
  {
    ballBTW = 1;
  }


  if (radio.available()) {

    radio.read(&text, sizeof(text));
    Serial.println(text);
  }

  // MPU



  if (ballBTW == 1)// condition to grip the shuttle
  {
    digitalWrite(sol, HIGH);

  }
  if (text == "throw")
  {
    //start the motor and start throwing the shuttle cock
    // throw upto the point where the gyro demands
    //then release the ball by the thread using the gripper motor driver
    delay(30);
    ballBTW = 0;
  }
  else
  {
    //remain in a vertical position
  }
  delay(50);

}
