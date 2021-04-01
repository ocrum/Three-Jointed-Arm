const float pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;
#include <math.h>
#include <Servo.h>
Servo clawServo; //make each servo
Servo servo2;
Servo servo3;
Servo servo4;

int x = 120;
int y = 260;



float toRadians(int degree) {
  return degree * (pi / 180);
}
int toDegrees(float radian) {
  return radian * (180 / pi);
}



int toAngle3(long xVal, long yVal) {
  if(xVal >= 0){
    return toDegrees(pi / 2 + acos(((double) (sq(xVal) + sq(yVal)) / sq(160) - 2) / 2));
  } else {
    return toDegrees(pi / 2 - acos(((double) (sq(xVal) + sq(yVal)) / sq(160) - 2) / 2));
  } 
}
int toAngle4(long xVal, long yVal) {
  if(xVal >= 0){
    float t = 2 * pi - (acos(((double) (sq(xVal) + sq(yVal)) / sq(160) - 2) / 2));
    float q = 160 + 160 * cos(t);
    float w = 160 * sin(t);
      
    int answer1 = toDegrees(asin((double)(w * xVal - q * yVal) / (double)(-1 * sq(w) - sq(q))));
    int answer2 = toDegrees(pi - asin((double)(w * xVal - q * yVal) / (double)(-1 * sq(w) - sq(q))));
      
    if (xVal > sqrt(yVal * 320 - sq(yVal))) {
      return answer1;
    } else {
      return answer2;
    }
  } else {
    float t = acos(((double) (sq(xVal) + sq(yVal)) / sq(160) - 2) / 2);
    float q = 160 + 160 * cos(t);
    float w = 160 * sin(t);
      
    int answer1 = toDegrees(asin((double)(w * xVal - q * yVal) / (double)(-1 * sq(w) - sq(q))));
    int answer2 = toDegrees(pi - asin((double)(w * xVal - q * yVal) / (double)(-1 * sq(w) - sq(q))));
      
    if (xVal > -1 * sqrt(yVal * 320 - sq(yVal))) {
      return answer1;
    } else {
      return answer2;
    }
  }
}



int first = 11; //port for claw servo
int second = 10; //port for top joint servo
int third = 9; //port for middle joint servo
int fourth = 6; //port for the bottom join servo

int cali4 = 5; //calibration becuase I hot glues stuff bad

int base1 = 180; //base position of servo
int base2 = 90;
int base3 = toAngle3(x, y);
int base4 = toAngle4(x, y);

int pos1 = base1; //setting posistion to base position
int pos2 = base2;
int pos3 = base4;
int pos4 = base4 + cali4;

char servo = '3'; //which servo is being edited

int change = 40;

void setup() {
  clawServo.attach(first); //attach each servo to their port1
  servo2.attach(second);
  servo3.attach(third);
  servo4.attach(fourth);
  Serial.begin(9600); //how fast you want the serial to read
  while (! Serial); //wait for serial to be ready
  Serial.println();
  printCord();
}



void loop() {
  if (Serial.available()) { //if there is something inputted into the serial
    char command = Serial.read(); //what is being read
    if (command == 'w') {
      if (isValidCord(x, y + change)) {
        if (toAngle3(x, y + change) != -1 && toAngle4(x, y + change) != -1) {
          y = y + change;
        }
      }
      printCord();
    } else if (command == 's') {
      if (isValidCord(x, y - change)) {
        if (toAngle3(x, y - change) != -1 && toAngle4(x, y - change) != -1) {
          y = y - change;
        } else {
        }
      }
      printCord();
    } else if (command == 'a') {
      if (isValidCord(x - change, y)) {
        if (toAngle3(x - change, y) != -1 && toAngle4(x - change, y) != -1) {
          x = x - change;
        }
      }
      printCord();
    } else if (command == 'd') {
      if (isValidCord(x + change, y)) {
        if (toAngle3(x + change, y) != -1 && toAngle4(x + change, y) != -1) {
          x = x + change;
        }
      }
      printCord();
    } else if (command == 'b') {
      Serial.println("The arm has been moved to the default posistion");
      x = 0;
      y = 320;
      printCord();
    } else if (command == 'o') {
      if (pos1 == 180) {
        pos1 = 90;
      } else if (pos1 == 90) {
        pos1 = 180;
      }
    }
  }

  if ((pos3 - pos4 + cali4 - 90) >= 0) { //perependicular
    pos2 = pos3 - pos4 + cali4 - 90;
  } else if ((pos3 - pos4 + cali4 - 90) <= -180) { //perpendicular
    pos2 = 360 + (pos3 - pos4 + cali4 - 90);
  } else if ((pos3 - pos4 + cali4 - 90) >= -95 && (pos3 - pos4 + cali4 - 90) <= -85) { //stright up
    pos2 = 90;
  } else if ((pos3 - pos4 + cali4 - 90) < -90) { //extreemes
    pos2 = 180;
  } else if ((pos3 - pos4 + cali4 - 90) > -90) {
    pos2 = 0;
  }

  pos3 = toAngle3(x, y);
  pos4 = toAngle4(x, y) + cali4;

  bool doDelay = false;
  //a smooth way of writing the servo (slowing stuff down)
  if (servo2.read() < pos2) {
    servo2.write(servo2.read() + 1);
    doDelay = true;
  }
  if (servo2.read() > pos2) {
    servo2.write(servo2.read() - 1);
    doDelay = true;
  }
  if (servo3.read() < pos3) {
    servo3.write(servo3.read() + 1);
    doDelay = true;
  }
  if (servo3.read() > pos3) {
    servo3.write(servo3.read() - 1);
    doDelay = true;
  }
  if (servo4.read() < pos4) {
    servo4.write(servo4.read() + 1);
    doDelay = true;
  }
  if (servo4.read() > pos4) {
    servo4.write(servo4.read() - 1);
    doDelay = true;
  }
  if(doDelay){
    delay(10);
  }
  clawServo.write(pos1); //always writes a servo to its position
}

void printCord(){
  Serial.print(" x = ");
  Serial.print(x);
  Serial.print(" y = ");
  Serial.print(y);
  Serial.print(" pos3 = ");
  Serial.print(toAngle3(x, y));
  Serial.print(" pos4 = ");
  Serial.println(toAngle4(x, y));
}

bool isValidCord(long xVal, long yVal) {
  return sqrt(sq(xVal) + sq(yVal)) <= 320;
}
