const float pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481;
#include <math.h>
#include <Servo.h>
Servo clawServo; //make each servo
Servo servo2;
Servo servo3;
Servo servo4;



int toAngle3(int xVal, int yVal) {
  int answer1 = -1 * toDegrees(pi / 2 - acos(((sq(xVal) + sq(yVal)) / sq(160) - 2) / 2));
  int answer2 = -1 * toDegrees(pi / 2 + acos(((sq(xVal) + sq(yVal)) / sq(160) - 2) / 2));

  int dif1 = abs(servo3.read() - answer1);
  int dif2 = abs(servo3.read() - answer2);

  if (min(dif1, dif2) = dif1) {
    if (answer1 < 0 || answer1 > 180) {
      if (answer2 < 0 || answer2 > 180) {
        return -1;
      } else {
        return answer2;
      }
    }
    return answer1;
  } else {
    if (answer2 < 0 || answer2 > 180) {
      if (answer1 < 0 || answer1 > 180) {
        return -1;
      } else {
        return answer1;
      }
    }
    return answer2;
  }
}
int toAngle4(int xVal, int yVal) {
  float t1 = pi - acos(((sq(xVal) + sq(yVal)) / sq(160) - 2) / 2);
  float t2 = 2 * pi - t1;
  float q1 = 160 + 160 * cos(t1);
  float q2 = 160 + 160 * cos(t2);
  float w1 = 160 * sin(t1);
  float w2 = 160 * sin(t2);

  int answer11 = toDegrees(asin((w1 * xVal - q1 * yVal) / (-1 * sq(w1) - sq(q1))));
  int answer12 = toDegrees(pi - asin((w1 * xVal - q1 * yVal) / (-1 * sq(w1) - sq(q1))));
  int answer21 = toDegrees(asin((w2 * xVal - q2 * yVal) / (-1 * sq(w2) - sq(q2))));
  int answer22 = toDegrees(pi - asin((w2 * xVal - q2 * yVal) / (-1 * sq(w2) - sq(q2))));

  int answer1 = -1;
  int answer2 = -1;

  if (xVal > sqrt(yVal * 320 - sq(yVal))) {
    answer2 = answer21;
  } else {
    answer2 = answer22;
  }

  if (xVal > -1 * sqrt(yVal * 320 - sq(yVal))) {
    answer1 = answer11;
  } else {
    answer1 = answer12;
  }

  int dif1 = abs(servo4.read() - answer1);
  int dif2 = abs(servo4.read() - answer2);

  if (min(dif1, dif2) = dif1) {
    if (answer1 < 0 || answer1 > 180) {
      if (answer2 < 0 || answer2 > 180) {
        return -1;
      } else {
        return answer2;
      }
    }
    return answer1;
  } else {
    if (answer2 < 0 || answer2 > 180) {
      if (answer1 < 0 || answer1 > 180) {
        return -1;
      } else {
        return answer1;
      }
    }
    return answer2;
  }
}



int first = 11; //ports for each servo
int second = 10;
int third = 9;
int fourth = 6;

int x = 200;
int y = 200;

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



void setup() {
  clawServo.attach(first); //attach each servo to their port1
  servo2.attach(second);
  servo3.attach(third);
  servo4.attach(fourth);
  Serial.begin(9600); //how fast you want the serial to read
  while (! Serial); //wait for serial to be ready
  Serial.println();
  Serial.print(" x = ");
  Serial.print(x);
  Serial.print(" y = ");
  Serial.print(y);
  Serial.print(" pos3 = ");
  int xVal = x;
  int yVal = y;
  Serial.print(-1 * toDegrees(pi / 2 - acos(((sq(xVal) + sq(yVal)) / sq(160) - 2) / 2)));
  Serial.print(" pos4 = ");
  Serial.println(toAngle4(x, y));
}



void loop() {
  if (Serial.available()) { //if there is something inputted into the serial
    char command = Serial.read(); //what is being read
    if (command == 'w') {
      if (isValidCord(x, y + 10)) {
        if (toAngle3(x, y + 10) != -1 && toAngle4(x, y + 10) != -1) {
          y = y + 10;
        }
      }
    } else if (command == 's') {
      if (isValidCord(x, y - 10)) {
        if (toAngle3(x, y - 10) != -1 && toAngle4(x, y - 10) != -1) {
          y = y - 10;
        }
      }
    } else if (command == 'a') {
      if (isValidCord(x - 10, y)) {
        if (toAngle3(x - 10, y) != -1 && toAngle4(x - 10, y) != -1) {
          x = x - 10;
        }
      }
    } else if (command == 'd') {
      if (isValidCord(x + 10, y)) {
        if (toAngle3(x + 10, y) != -1 && toAngle4(x + 10, y) != -1) {
          x = x + 10;
        }
      }
    } else if (command == 'b') {
      Serial.println("The arm has been moved to the default posistion");
      pos1 = base1; //position for each servo
      pos2 = base2;
      pos3 = base3;
      pos4 = base4 + cali4;
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
  return degree * (pi / 180);
}

int toDegrees(float radian) {
  return radian * (180 / pi);
}



bool isValidCord(int xVal, int yVal) {
  return sqrt(sq(xVal) + sq(yVal)) <= 320;
}
