#include <Omni.h>
#include <Drive.h>
#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(10, 11); // SoftwareSerial: Rx and Tx pin

int x,y;

Drive manBotDrive = Drive();
int pwms[] = {3, 2, 5};
int dirs[] = {29, 25, 33};
int brks[] = {27, 23, 31};

void setup()
{
  Serial.begin(9600);
  ps2.begin(9600);
  Serial.println("PS2 Remote_Cytron Shield");
  Serial.println("Press Start");

//  while ((ps2.getval(p_start)));

  Serial.println("Good");
  manBotDrive.init(pwms, dirs, brks);
  delay(500);
  Serial.println("Initialize success");
  delay(1000);


}

void loop()
{
    x = PS2_JOYSTICK_LEFT_X_AXIS;
    y = PS2_JOYSTICK_LEFT_Y_AXIS;
    
    if (x > 200 && (y < 200 && y > 55)) {
      manBotDrive.moveright();
    }
    else if (x < 55 && (y < 200 && y > 55)) {
      manBotDrive.moveleft();
    }
    else if (y < 55 && (x < 200 && x > 55)){
      manBotDrive.movebackward();
    }
    else if (y > 200 && (x < 200 && x > 55)){
      manBotDrive.moveforward();
    }
    delay(50);
}
