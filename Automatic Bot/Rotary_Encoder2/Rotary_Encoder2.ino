short int counter = 0;  //This variable will increase or decrease depending on the rotation of encoder

int encoder = {2, 3};

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(encoder[1]) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(encoder[0]) == LOW) {
    counter--;
  } else {
    counter++;
  }
}

void setup() {
  Serial.begin (9600);

  pinMode(encoder[0], INPUT);// set pin to input
  pinMode(encoder[1], INPUT);// set pin to input
  digitalWrite(encoder[0], HIGH);       // turn on pullup resistors
  digitalWrite(encoder[1], HIGH);       // turn on pullup resistors


  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
}

void loop() {
  // Send the value of counter
  Serial.println (counter);
}