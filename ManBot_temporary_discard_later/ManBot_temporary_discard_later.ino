/*
This example shows how to read a joystick value on PS2 Controller.

Function:
  readButton(button); // Read button status, it will return corresponding data
                      // Digital button: 0 = pressed, 1 = released
                      // Analog button: return a value

  Digital button:
    PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UP
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE

  Analog button:
    PS2_JOYSTICK_LEFT_X_AXIS
    PS2_JOYSTICK_LEFT_Y_AXIS
    PS2_JOYSTICK_RIGHT_X_AXIS
    PS2_JOYSTICK_RIGHT_Y_AXIS
    PS2_JOYSTICK_LEFT_UP
    PS2_JOYSTICK_LEFT_DOWN
    PS2_JOYSTICK_LEFT_LEFT
    PS2_JOYSTICK_LEFT_RIGHT
    PS2_JOYSTICK_RIGHT_UP
    PS2_JOYSTICK_RIGHT_DOWN
    PS2_JOYSTICK_RIGHT_LEFT
    PS2_JOYSTICK_RIGHT_RIGHT

Product page:
  Cytron PS2 Shield: http://www.cytron.com.my/p-shield-ps2
  PS2 Controller: http://www.cytron.com.my/p-ps-gp-1
  CT-UNO: http://www.cytron.com.my/p-ct-uno

Original written by:
            Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies
*/

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
#include <Servo.h>
#include <math.h>
#include <Omni.h>
// #include <Drive.h>
int x, y, w, z, L1, L2, R1, R2;
Servo myservo1, myservo2, myservo3; // create servo object to control a servo
Omni motor1(3, 29, 27);
Omni motor2(2, 25, 23);
Omni motor3(5, 33, 31);
// Drive drivemotion(&motor1, &motor2, &motor3);
Cytron_PS2Shield ps2(10, 11); // SoftwareSerial: Rx and Tx pin

//Cytron_PS2Shield ps2; // HardwareSerial, note:
int angle;
const int stepPin1 = 37;
const int dirPin1 = 35;
const int stepPin2 = 45;
const int dirPin2 = 43;
const int stepPin3 = 41;
const int dirPin3 = 39;
void setup()
{
  myservo1.attach(8);
  myservo2.attach(7);
  myservo3.attach(6);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600); // Set monitor baudrate to 9600
  motor1.stopped();
  motor2.stopped();
  motor3.stopped();
}



void loop()
{ /*
   motor1.forward();
   motor2.forward();
   motor3.forward();
   delay(1000);
   motor1.backward();
   motor2.backward();
   motor3.backward();
   delay(1000);
   motor1.stopped();
   motor2.stopped();
   motor3.stopped();
   delay(1000);
   */
  //myservos are detached inside the readbuttonfunction whereas they are attached inside every button press and written a default state //
  if (ps2.readAllButton())
  {
    myservo1.detach();
    myservo2.detach();
    myservo3.detach();
    x = ps2.readButton(PS2_JOYSTICK_RIGHT_LEFT);
    y = ps2.readButton(PS2_JOYSTICK_RIGHT_RIGHT);
    z = ps2.readButton(PS2_JOYSTICK_RIGHT_UP);
    w = ps2.readButton(PS2_JOYSTICK_RIGHT_DOWN);
    L1 = ps2.readButton(PS2_LEFT_1);
    L2 = ps2.readButton(PS2_LEFT_2);
    R1 = ps2.readButton(PS2_RIGHT_1);
    R2 = ps2.readButton(PS2_RIGHT_2);
  }
  if (z > 20)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);
    motor1.stopped();
    motor2.backward();
    motor3.forward();
    Serial.println(z);

  }
  else if (w > 20)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);
    motor1.stopped();
    motor2.forward();
    motor3.backward();
    Serial.println(w);

  }
  else if (x > 20)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);
    motor1.backward();
    motor2.forward();
    motor3.forward();
    Serial.println(x);

  }
  else if (y > 20)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);
    motor1.forward();
    motor2.backward();
    motor3.backward();
    Serial.println(y);

  }
  else if (!L1)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);
    motor1.stopped();
    motor2.stopped();
    motor3.stopped();
    digitalWrite(dirPin1, HIGH);
    digitalWrite(dirPin2, HIGH);
    digitalWrite(dirPin3, HIGH);
    for (int x = 0; x < 40; x++)
    {
      digitalWrite(stepPin1, HIGH);
      digitalWrite(stepPin2, HIGH);
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      digitalWrite(stepPin2, LOW);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(2000);
    }
  }
  else if (!L2)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo2.write(60);
    myservo3.write(90);
    myservo1.write(70);
    motor1.stopped();
    motor2.stopped();
    motor3.stopped();
  }
  else if (!R1)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo3.write(90);
    myservo2.write(90);
    motor1.stopped();
    motor2.stopped();
    motor3.stopped();
  }

  else if (!R2)
  {
    myservo1.attach(8);
    myservo2.attach(7);
    myservo3.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(120);
    motor1.stopped();
    motor2.stopped();
    motor3.stopped();
  }

  else
  {
    motor1.stopped();
    motor2.stopped();
    motor3.stopped();
    myservo1.attach(8);
    myservo1.attach(7);
    myservo1.attach(6);
    myservo1.write(35);
    myservo2.write(60);
    myservo3.write(90);

  }/*
  drivemotion.moveforward(&motor1,&motor2,&motor3);
  delay(1000);
  drivemotion.stopped(&motor1,&motor2,&motor3);
  delay(1000);
  drivemotion.movebackward(&motor1,&motor2,&motor3);
  delay(1000);
  drivemotion.stopped(&motor1,&motor2,&motor3);
  delay(1000);
  */
}

