#include <Servo.h>
const float pi = 3.1415926535;
int first = 11; //ports for each servo
int second = 10;
int third = 9;
int fourth = 6;
int cali4 = 5; //calibration becuase I hot glues stuff bad
int base1 = 180; //base position of servo
int base2 = 90;
int base3 = 90;
int base4 = 90;
int pos1 = base1; //setting posistion to base position
int pos2 = base2;
int pos3 = base3;
int pos4 = base4 + cali4;
int x = -1; //the x and y cords
int y = -1;
Servo clawServo; //make each servo
Servo servo2;
Servo servo3;
Servo servo4;
char servo = '3'; //which servo is being edited
int change = 30; //how much you change the servos position

void setup() {
  clawServo.attach(first); //attach each servo to their port1
  servo2.attach(second);
  servo3.attach(third);
  servo4.attach(fourth);
  Serial.begin(9600); //how fast you want the serial to read
  while (! Serial); //wait for serial to be ready
  Serial.println();
}

void loop() {
  x = 160 * cos(toRadians(pos4 - cali4)) + 160 * cos(toRadians((90 - pos3 + (pos4 - cali4))));
  y = 160 * sin(toRadians(pos4 - cali4)) + 160 * sin(toRadians((90 - pos3 + (pos4 - cali4))));
  
  if (Serial.available()) { //if there is something inputted into the serial
    char command = Serial.read(); //what is being read
    if (command == '3' || command == '4') { //if it is a number
      Serial.print("You are currently using servo number ");
      Serial.println(command);
      servo = command; //set the servo to be edited to the servo
    } else if (command == '<') { //decrement command
      if (servo == '3') {
        if (pos3 - change >= 0) {
          pos3 = pos3 - change;
          Serial.println(pos3);
        } else {
          Serial.println("This servo can't move past this angle");
        }
      } else if (servo == '4') {
        if (pos4 + change <= 180) {
          pos4 = pos4 + change;
          Serial.println(pos4);
        } else {
          Serial.println("This servo can't move past this angle");
        }
      }
    } else if (command == '>') { //increment command
      if (servo == '3') {
        if (pos3 + change <= 180) {
          pos3 = pos3 + change;
          Serial.println(pos3);
        } else {
          Serial.println("This servo can't move past this angle");
        }
      } else if (servo == '4') {
        if (pos4 - change >= 0) {
          pos4 = pos4 - change;
          Serial.println(pos4);
        } else {
          Serial.println("This servo can't move past this angle");
        }
      }
    } else if (command == 'o') {
      if (pos1 == 180) {
        pos1 = 90;
      } else if (pos1 == 90) {
        pos1 = 180;
      }
    } else if (command == 'b') {
      Serial.println("The arm has been moved to the default posistion");
      pos1 = base1; //position for each servo
      pos2 = base2;
      pos3 = base3;
      pos4 = base4 + cali4;
    }
  }
  
  if ((pos3 - pos4 + cali4 - 90) >= 0) { //perependicular
    pos2 = pos3 - pos4 + cali4 - 90;
  } else if((pos3 - pos4 + cali4 - 90) <= -180){ //perpendicular
    pos2 = 360+(pos3 - pos4 + cali4 - 90);
  } else if((pos3 - pos4 + cali4 - 90) >= -95 && (pos3 - pos4 + cali4 - 90) <= -85){ //stright up
    pos2 = 90;
  } else if((pos3 - pos4 + cali4 - 90) < -90){ //bleh don't know how to explain this in a nice and concise way...
    pos2 = 180;
  } else if((pos3 - pos4 + cali4 - 90) >-90){
    pos2 = 0;
  }
  
  //a smooth way of writing the servo (slowing stuff down)
  if (servo2.read() < pos2) {
    servo2.write(servo2.read() + 1);
    delay(15);
  }
  if (servo2.read() > pos2) {
    servo2.write(servo2.read() - 1);
    delay(15);
  }
  if (servo3.read() < pos3) {
    servo3.write(servo3.read() + 1);
    delay(15);
  }
  if (servo3.read() > pos3) {
    servo3.write(servo3.read() - 1);
    delay(15);
  }
  if (servo4.read() < pos4) {
    servo4.write(servo4.read() + 1);
    delay(15);
  }
  if (servo4.read() > pos4) {
    servo4.write(servo4.read() - 1);
    delay(15);
  }
  clawServo.write(pos1); //always writes a servo to its position
}

float toRadians(int degree) {
  return degree * pi / 180;
}
