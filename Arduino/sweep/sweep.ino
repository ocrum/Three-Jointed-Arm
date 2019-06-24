#include <Servo.h>
int first = 11; //ports for each servo
int second = 10;
int third = 9;
int fourth = 6;
int pos1 = 0; //position for each servo
int pos2 = 180;
int pos3 = 0;
int pos4 = 0;
Servo servo1; //make each servo
Servo servo2;
Servo servo3;
Servo servo4;
char servo = '1'; //which servo is being edited
int change = 30; //how much you change the servos position

void setup() {
  servo1.attach(first); //attach each servo to their port
  servo2.attach(second);
  servo3.attach(third);
  servo4.attach(fourth);
  Serial.begin(9600); //how fast you want the serial to read
  while (! Serial); //wait for serial to be ready
  Serial.println("Type something");
}

void loop() {
  servo1.write(pos1); //always writes a servo to its position
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  
  if (Serial.available()) { //if there is something inputted into the serial
    char command = Serial.read(); //what is being read
    if(command == '1' || command == '2' || command == '3' || command == '4'){ //if it is a number
      Serial.print("You are currently using servo number ");
      Serial.println(command);
      servo = command; //set the servo to be edited to the servo
    } else if(command == '<'){ //decrement command
      if(servo == '1'){ //for the specified servo
        if(pos1 - change >= 0){ //if the change will go out of bounds
          pos1 = pos1 - change; //change position
        }
      } else if(servo == '2'){
        if(pos2 - change >= 90){
          pos2 = pos2 - change;
          Serial.println(pos2);
        }
      } else if(servo == '3'){
        if(pos3 - change >= 0){
          pos3 = pos3 - change;
        }
      } else if(servo == '4'){
        if(pos4 - change >= 0){
          pos4 = pos4 - change;
        }
      }
    } else if(command == '>'){ //increment command
      if(servo == '1'){
        if(pos1 + change <= 180){
          pos1 = pos1 + change;
        }
      } else if(servo == '2'){
        if(pos2 + change <= 180){
          pos2 = pos2 + change;
        }
      } else if(servo == '3'){
        if(pos2 + change <= 180){
          pos3 = pos3 + change;
        }
      } else if(servo == '4'){
        if(pos2 + change <= 180){
          pos4 = pos4 + change;
        }
      }
    }
  }
}
