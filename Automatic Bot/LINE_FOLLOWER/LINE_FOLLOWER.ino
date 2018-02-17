
int lf = 9;
int rf = 10; 
int rb = 11;
int lb = 12;
void setup() {
  // put your setup code here, to run once:
 
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
   pinMode(8, INPUT);
  
  pinMode(lf, OUTPUT);
  pinMode(lb, OUTPUT);
  pinMode(rf,OUTPUT);
  pinMode(rb, OUTPUT);

   digitalWrite(lf ,LOW);
   digitalWrite(lb ,LOW);
   digitalWrite(rf ,LOW);
   digitalWrite(rb ,LOW);
}


void loop() {
  // put your main code here, to run repeatedly:
   if(digitalRead(2) && digitalRead(5))
  moveForward();
  
  // Checking for sensor number 1 and 2, if line detected, move left
  else if(digitalRead(1) || digitalRead(2))
  moveLeft();

  // Checking for sensor number 5 and 6, if line detected, move right
  else if(digitalRead(5) || digitalRead(6))
  moveRight();

  // Checking for sensors number 3 and 4, 
  // if line is detected by either of these sensor, move forward
  else if(digitalRead(3) || digitalRead(4))
  moveForward();

  // If no line is detected, stay at the position
  else
  wait();

  // Put some delay to avoid the robot jig while making a turn
  delay(100);
  

}


void moveRight () {

  digitalWrite(lf,LOW);

  digitalWrite(lb,LOW);

  digitalWrite(rb,LOW);

  digitalWrite(rf, HIGH);

}

void moveForward () {

  digitalWrite(lb,LOW);

digitalWrite(rb,LOW);

digitalWrite(lf,HIGH);

digitalWrite(rf,HIGH);


}

void moveLeft () {

    digitalWrite(lf,HIGH);

  digitalWrite(lb,LOW);

  digitalWrite(rb,LOW);

  digitalWrite(rf, LOW); 
  }


void wait() {

  digitalWrite(lf, LOW);

  digitalWrite(lb,LOW);

  digitalWrite(rb,LOW);

  digitalWrite(rf, LOW); 
  }

  

   

  

 








  


