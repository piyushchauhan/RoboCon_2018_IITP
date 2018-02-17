//Edited by Bhushan Deo 1501EE50
//no copyrights intended

#include <driveMotion.h>
 // Install Pin change interrupt for a pin, can be called multiple times
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
     node_encountered+=(digitalRead(8)&digitalRead(9)&digitalRead(10)&digitalRead(11)&digitalRead(12)&digitalRead(13)); //node_encountered
     forward = (!digitalRead(8)&!digitalRead(9)&digitalRead(10)&digitalRead(11)&!digitalRead(12)&!digitalRead(13)); // forward
     right = (digitalRead(8)|digitalRead(9));//right any one of the two sensors is high then go right
     left = (digitalRead(12)|digitalRead(13));//right any one of the two sensors is high then go left 
 } 
/*
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
     digitalWrite(13,digitalRead(A0));
 }  

ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(7)); 
 }  
 */
driveMotion drivemotion();            //  create the library driveMotion and it's object is drivemotion //take proper arguments
void setup() {   
int i; 
node_encountered=0;
// check to see whether pull ups are necessary 

  for (i=8; i<=13; i++) 
      pinMode(i,INPUT);  // pinMode( ,INPUT) is default
// enable interrupt for pin...
  pciSetup(8);
  pciSetup(9);
  pciSetup(10);
  pciSetup(11);
  pciSetup(12);
  pciSetup(13);
  
 
}


void loop() {
  // Nothing needed
  if(node_encountered>=2)
  {
    drivemotion.stopped();            // stop all the motors goal reached start throwing give signal to nrf //after throwing bring back robot to 
    //original position and reset node_encountered 
    node_encountered=0;
    Serial.println("Node is encountered , stop the robot  throw and reset ");
  }
  else if(node_encountered<2)
  {
   if(forward & !right & !left & !nosensor )
   {
    drivemotion.goforward();  // forward is being set in the ISR 
    Serial.println("Go Forward");
   }
   else if(!forward & right & left & !nosensor)
   {
    drivemotion.goright();   // right is being set in the ISR    
    Serial.println("Go Right");             
   }
   else if(!forward & !right & left & !nosensor)
   {
    drivemotion.goleft();   // left is being set in the ISR    
    Serial.println("Go Left");             
   }
   else if(!forward & !right & !left & nosensor)
   {
    // no sensor is high please stop the robot 
    drivemotion.stopped();                
    Serial.println("Don't move");
   }
  }
  delay(100); // appropriate delay choose accordingly
}
