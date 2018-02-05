#include <Omni.h>
#include <Drive.h>
Drive manBotDrive = Drive();
int pwms[] = {2,5,8};
int dirs[] = {3,6,9};
int brks[] = {4,7,11};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  manBotDrive.init(pwms, dirs, brks);
  delay(1000);
  Serial.println("Initialize success");
  delay(1000);
}

void loop() {
  manBotDrive.moveforward();
  delay(500);
  manBotDrive.movebackward();
  delay(500);
  manBotDrive.moveright();
  delay(500);
  manBotDrive.moveleft();
  delay(2000);
  // put your main code here, to run repeatedly:

}
