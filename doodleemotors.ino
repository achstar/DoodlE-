#include <AFMotor.h>

//Define the sensor pins
#define S1Trig A0
#define S2Trig A1
#define S3Trig A2
#define S1Echo A3
#define S2Echo A4
#define S3Echo A5

//Set the speed of the motors
#define Speed 200

//Create objects for the motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

byte maxDist = 150;                               //Maximum sensing distance (Objects further than this distance are ignored)
byte stopDist = 30;                               //Minimum distance from an object to stop in cm
float timeOut = 2*(maxDist+10)/100/340*1000000;   //Maximum time to wait for a return signal

void setup() {
  Serial.begin(9600);

  //Set the Trig pins as output pins
  pinMode(S1Trig, OUTPUT);
  pinMode(S2Trig, OUTPUT);
  pinMode(S3Trig, OUTPUT);

  //Set the Echo pins as input pins
  pinMode(S1Echo, INPUT);
  pinMode(S2Echo, INPUT);
  pinMode(S3Echo, INPUT);

  //Set the speed of the motors
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);
}

void loop() {
  int sensor1 = getDistance(S1Trig, S1Echo);
  int sensor2 = getDistance(S2Trig, S2Echo);
  int sensor3 = getDistance(S3Trig, S3Echo);

  if(sensor2 >= stopDist){
    Serial.println("Forward");
    switchDir("forward");
  } else if(sensor1 >= stopDist){
    Serial.println("Left");
    switchDir("left");
  } else if(sensor3 >= stopDist){
    Serial.println("Right");
    switchDir("right");
  }

  while(sensor2 >= stopDist){
    sensor2 = getDistance(S2Trig, S2Echo);
    delay(250);
  }

  Serial.println("Stop");
  switchDir("stop");
}

//Get the sensor values
int getDistance(int trig, int echo) {
  //pulse output
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long pulseTime = pulseIn(echo, HIGH, timeOut);//Get the pulse
  int distance = (float)pulseTime * 340 / 2 / 10000; //Convert time to the distance
  Serial.println(distance);
  return distance; // Return the values from the sensor
}

/******Motor functions*******/
void switchDir(String dir)
{
  if(dir.equals("forward")){
    motor4.run(FORWARD);
    motor3.run(FORWARD);
    motor2.run(FORWARD);
    motor1.run(FORWARD);
  }
  else if(dir.equals("backward")){
    motor4.run(BACKWARD);
    motor3.run(BACKWARD);
    motor2.run(BACKWARD);
    motor1.run(BACKWARD);
  }
  else if(dir.equals("right")){
    motor4.run(FORWARD);
    motor3.run(BACKWARD);
    motor2.run(FORWARD);
    motor1.run(BACKWARD);
  }
  else if(dir.equals("left")){
    motor4.run(BACKWARD);
    motor3.run(FORWARD);
    motor2.run(BACKWARD);
    motor1.run(FORWARD);
  }
  else if(dir.equals("rightDiagF")){
    motor4.run(FORWARD);
    motor3.run(RELEASE);
    motor2.run(FORWARD);
    motor1.run(RELEASE);
  }
  else if(dir.equals("rightDiagB")){
    motor4.run(BACKWARD);
    motor3.run(RELEASE);
    motor2.run(BACKWARD);
    motor1.run(RELEASE);
  }
  else if(dir.equals("leftDiagF")){
    motor4.run(RELEASE);
    motor3.run(FORWARD);
    motor2.run(RELEASE);
    motor1.run(FORWARD);
  }
  else if(dir.equals("leftDiagB")){
    motor4.run(RELEASE);
    motor3.run(BACKWARD);
    motor2.run(RELEASE);
    motor1.run(BACKWARD);
  }
  else if(dir.equals("concerningR")){
    motor4.run(FORWARD);
    motor3.run(RELEASE);
    motor2.run(RELEASE);
    motor1.run(FORWARD);
  }
  else if(dir.equals("concerningL")){
    motor4.run(RELEASE);
    motor3.run(FORWARD);
    motor2.run(FORWARD);
    motor1.run(RELEASE);
  }
  else if(dir.equals("turnRound")){
    motor4.run(FORWARD);
    motor3.run(BACKWARD);
    motor2.run(BACKWARD);
    motor1.run(FORWARD);
  }
  else if(dir.equals("stop")) {
    motor4.run(RELEASE);
    motor3.run(RELEASE);
    motor2.run(RELEASE);
    motor1.run(RELEASE);
  }
}
