#include <Servo.h>
int first = 11; //ports for each servo
int second = 10;
int third = 9;
int fourth = 6;
int pos1 = 180; //position for each servo
int pos2 = 90;
int pos3 = 90;
int pos4 = 95;
Servo clawServo; //make each servo
Servo servo2;
Servo servo3;
Servo servo4;
char servo = '1'; //which servo is being edited
int change = 30; //how much you change the servos position

void setup() {
  clawServo.attach(first); //attach each servo to their port
  servo2.attach(second);
  servo3.attach(third);
  servo4.attach(fourth);
  Serial.begin(9600); //how fast you want the serial to read
  while (! Serial); //wait for serial to be ready
  Serial.println("Type something");
}

void loop() {
  clawServo.write(pos1); //always writes a servo to its position
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);

  if (Serial.available()) { //if there is something inputted into the serial
    char command = Serial.read(); //what is being read
    if (command == 'w') { 
      
    } else if (command == 's'){
      
    } else if (command == 'a'){
      
    } else if (command == 'd'){
      
    }
//      Serial.print("You are currently using servo number ");
//      Serial.println(command);
//      servo = command; //set the servo to be edited to the servo
//    } else if (command == '<') { //decrement command
//      if (servo == '1') { //for the specified servo
//        if (pos1 - change >= 90) { //if the change will go out of bounds
//          pos1 = pos1 - change; //change positionw
//          Serial.println(pos1);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '2') {
//        if (pos2 - change >= 0) {
//          pos2 = pos2 - change;
//          Serial.println(pos2);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '3') {
//        if (pos3 - change >= 0) {
//          pos3 = pos3 - change;
//          Serial.println(pos3);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '4') {
//        if (pos4 - change >= 0) {
//          pos4 = pos4 - change;
//          Serial.println(pos4);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      }
//    } else if (command == '>') { //increment command
//      if (servo == '1') {
//        if (pos1 + change <= 180) {
//          pos1 = pos1 + change;
//          Serial.println(pos1);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '2') {
//        if (pos2 + change <= 180) {
//          pos2 = pos2 + change;
//          Serial.println(pos2);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '3') {
//        if (pos3 + change <= 180) {
//          pos3 = pos3 + change;
//          Serial.println(pos3);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      } else if (servo == '4') {
//        if (pos4 + change <= 180) {
//          pos4 = pos4 + change;
//          Serial.println(pos4);
//        } else {
//          Serial.println("This servo can't move past this angle");
//        }
//      }
//    }
  }
}
