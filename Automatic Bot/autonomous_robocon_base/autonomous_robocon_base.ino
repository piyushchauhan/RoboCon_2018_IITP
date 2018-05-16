//Edited by Bhushan Deo 1501EE50
//no copyrights intended
//We're working with 5 IR sensors in each array not 6 , IMPORTANT
//#include <driveMotion.h>
// Install Pin change interrupt for a pin, can be called multiple times

#include <driveMotion.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

driveMotion drivemotion = driveMotion();
int pwms[4] = {2, 3, 5, 4};
int dirs[4] = {23, 27, 37, 33};
int brks[4] = {25, 29, 35, 31};
int thowmotor[3] = {6, 41, 39}; // pwm, dir, brk

int ballGoneFlag = 0; // Tracks data from the RPi

RF24 radio(7, 8); // CE, CSN
// const byte address[6] = '00001';
const byte address[][6] = {"00001", "00002"};

int encoderPin1 = A0;
int encoderPin2 = A1;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;
volatile int MSB , LSB , encoded , sum; // for the interrupt pins of the encoder

int lastMSB = 0;
int lastLSB = 0;
int node_encountered ;    //determine the number of nodes encountered
int forward , right , left , nosensor ; //forward , right , left , no sensor is on variables
void pciSetup(byte pin)
{
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

// Use one Routine to handle each group

ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{
  // LSA08
  node_encountered += (digitalRead(9)&digitalRead(10)&digitalRead(11)&digitalRead(12)&digitalRead(13)); //node_encountered
  forward = (!digitalRead(9) & !digitalRead(10)&digitalRead(11) & !digitalRead(12) & !digitalRead(13)); // forward
  right = (digitalRead(9) | digitalRead(10)); // any one of the two sensors is high then go right
  left = (digitalRead(12) | digitalRead(13)); // any one of the two sensors is high then go left
}

ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
  // Encoders
  MSB = digitalRead(encoderPin1); //MSB = most significant bit
  LSB = digitalRead(encoderPin2); //LSB = least significant bit
  encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
/*
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(7));
 }
 */
//driveMotion drivemotion();            //  create the library driveMotion and it's object is drivemotion //take proper arguments
void setup() {
  int i;
  node_encountered = 0;
  // check to see whether pull ups are necessary

  // Mechanum pins
  drivemotion.init(pwms, dirs, brks);


  // LSA08 Pins
  for (i = 9; i <= 13; i++)
    pinMode(i, INPUT); // pinMode( ,INPUT) is default
  // enable interrupt for pin...

  // Interupts of Pin Change Interupt Library(PCI)
  pciSetup(9);
  pciSetup(10);
  pciSetup(11);
  pciSetup(12);
  pciSetup(13);

  // NRF Communication
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1,address[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)

}


void loop() {
  Serial.println(encoderValue);

  // Nothing needed
  if (node_encountered >= 2)
  {
    //drivemotion.stopped();            // stop all the motors goal reached start throwing give signal to nrf //after throwing bring back robot to
    //original position and reset node_encountered
    radio.stopListening();
    node_encountered = 0;
    Serial.println("Node is encountered , stop the robot  throw and reset ");
    const char text[] = "throw";
    radio.write(&text, sizeof(text));
    delay(100);


    // NRF communication begins


    // Throwing

    // Feedback from pi camera
    if (Serial.available())
    {
      ballGoneFlag = Serial.read() - '0';
    }
    /*if ball goes from the ring ballGoneFlag will be 1 else 0*/
  }


  else if (node_encountered < 2)
  {
    if (forward & !right & !left & !nosensor )
    {
      drivemotion.moveforward();// forward is being set in the ISR
      Serial.println("Go Forward");
    }
    else if (!forward & right & left & !nosensor)
    {
      drivemotion.moveright();   // right is being set in the ISR
      Serial.println("Go Right");
    }
    else if (!forward & !right & left & !nosensor)
    {
      drivemotion.moveleft();   // left is being set in the ISR
      Serial.println("Go Left");
    }
    else if (!forward & !right & !left & nosensor)
    {
      // no sensor is high please stop the robot
      drivemotion.mstop();
      Serial.println("Don't move");
    }
  }
  delay(100); // appropriate delay choose accordingly
}

