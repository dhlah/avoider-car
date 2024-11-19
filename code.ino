#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 200 

int speedLeft = 180;   // Speed for left motor
int speedRight = 180;  // Speed for right motor
int speedTurnLeft = 80
int speedTurnRight = 80

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); // Left motor
AF_DCMotor motor2(2, MOTOR12_1KHZ); // Right motor
Servo myservo;   

boolean goesForward = false;
int distance = 100;

void setup() {
  myservo.attach(10);  
  myservo.write(90);  
  delay(2000);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  myservo.write(0);  
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);  
  return distance;
}

int lookLeft() {
  myservo.write(180);  
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(90);  
  return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
} 
  
void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor1.setSpeed(speedLeft);
    motor2.setSpeed(speedRight);
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor1.setSpeed(150);
  motor2.setSpeed(150);
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(speedTurnLeft);  // Reduce speed for turning
  motor2.setSpeed(speedTurnRight);
  delay(1000);
}

void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);
  motor1.setSpeed(speedTurnLeft);  // Reduce speed for turning
  motor2.setSpeed(speedTurnRight);
  delay(1000);
}
