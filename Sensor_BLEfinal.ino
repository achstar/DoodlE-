
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

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);
AF_DCMotor motor2(2);
AF_DCMotor motor1(1);

byte maxDist = 150;                               //Maximum sensing distance (Objects further than this distance are ignored)
byte stopDist2 = 10;
byte stopDist = 10;                               //Minimum distance from an object to stop in cm
float timeOut = 2*(maxDist+10)/100/340*1000000;   //Maximum time to wait for a return signal

char junk;
String inputString="";

void setup() 
{
  Serial.begin(9600);
    //Set the Trig pins as output pins
  pinMode(S1Trig, OUTPUT);
  pinMode(S2Trig, OUTPUT);
  pinMode(S3Trig, OUTPUT);

  //Set the Echo pins as input pins
  pinMode(S1Echo, INPUT);
  pinMode(S2Echo, INPUT);
  pinMode(S3Echo, INPUT);
  
  //Set initial speed of the motor & stop
  motor4.setSpeed(Speed);
  motor4.run(RELEASE);

  motor3.setSpeed(Speed);
  motor3.run(RELEASE);

  motor2.setSpeed(Speed);
  motor2.run(RELEASE);

  motor1.setSpeed(Speed);
  motor1.run(RELEASE);
}

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

void turnAngle(uint8_t angle) {
    
    motor4.run(RELEASE);
    motor3.run(FORWARD);
    motor2.run(FORWARD);
    motor1.run(RELEASE);
    uint8_t i;
    for (i=0; i<255; i++) {
      setSpeeds(i, i, i, i);
      delay(10);
    }
}

void setSpeeds(uint8_t sp1, uint8_t sp2, uint8_t sp3, uint8_t sp4) 
{
    motor4.setSpeed(sp4);
    motor3.setSpeed(sp3);  
    motor2.setSpeed(sp2);
    motor1.setSpeed(sp1);
}

void testMotors() {
  
  uint8_t i;
  // Now change motor direction
  motor4.run(FORWARD);
  motor3.run(FORWARD);
  motor2.run(FORWARD);
  motor1.run(FORWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    setSpeeds(i, i, i, i);  
    delay(10);
  }
  
  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    setSpeeds(i, i, i, i);       
    delay(10);
  }

  // Now change motor direction
  motor4.run(BACKWARD);
  motor3.run(BACKWARD);
  motor2.run(BACKWARD);
  motor1.run(BACKWARD);
  
  // Accelerate from zero to maximum speed
  for (i=0; i<255; i++) 
  {
    motor4.setSpeed(i);
    motor3.setSpeed(i);   
    motor2.setSpeed(i);
    motor1.setSpeed(i);  
    delay(10);
  }

  // Decelerate from maximum speed to zero
  for (i=255; i!=0; i--) 
  {
    motor4.setSpeed(i);
    motor3.setSpeed(i);   
    motor2.setSpeed(i);
    motor1.setSpeed(i);  
    delay(10);
  }

  // Now turn off motor
  motor4.run(RELEASE);
  motor3.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
  delay(1000);
}

void loop() 
{
  int sensor1 = getDistance(S1Trig, S1Echo);
  int sensor2 = getDistance(S2Trig, S2Echo);
  int sensor3 = getDistance(S3Trig, S3Echo);
  uint8_t i;
  
  if (Serial.available() > 0) {
    while(Serial.available()){
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    
    junk = Serial.read() ; 
    
    if (inputString == "f") {
      if(sensor2 >= stopDist2){
        // Now change motor direction
        switchDir("forward");
        setSpeeds(200, 200, 200, 200);
        Serial.write("forward");
      }
      else{
        switchDir("stop");
        delay(100);
        switchDir("backward");
      }
     } 
    
    if (inputString == "b") {
      switchDir("backward");
      setSpeeds(255, 255, 255, 255);
      Serial.write("backward");
    }
    
    if(inputString == "s") {
      switchDir("stop");
      Serial.write("stop");
    }
    
    if(inputString == "r"){
      if(sensor3 >= stopDist){
        // Now change motor direction
        switchDir("right");
        setSpeeds(255, 255, 255, 255);      
        Serial.write("right");
      }
      else{
        switchDir("left");
        setSpeeds(255, 255, 255, 255);
        Serial.write("left");
      }
    }
    
    if(inputString == "l") {
       if(sensor1 >= stopDist){
        // Now change motor direction
        switchDir("left");
        setSpeeds(255, 255, 255, 255);
        Serial.write("left");
      }
      else{
        switchDir("right");
        setSpeeds(255, 255, 255, 255);
        Serial.write("right");
      }  
    }

  inputString = "";
  }
}

  //Get the sensor values
int getDistance(int trig, int echo) {
  //pulse output
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  unsigned long pulseTime = pulseIn(echo, HIGH, timeOut);//Get the pulse
  int distance = (float)pulseTime * 340 / 2 / 10000; //Convert time to the distance
  return distance; // Return the values from the sensor
}

////////////////////////////////////////////////////////////////////////////////

//char junk;
//String inputString="";
//
//void setup()                    // run once, when the sketch starts
//{
// Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
// pinMode(13, OUTPUT);
//}

//void loop()
//{
//  if(Serial.available()){
//  while(Serial.available())
//    {
//      char inChar = (char)Serial.read(); //read the input
//      inputString += inChar;        //make a string of the characters coming on serial
//    }
//    Serial.println(inputString);
//    while (Serial.available() > 0)  
//    { junk = Serial.read() ; }      // clear the serial buffer
//    if(inputString == "a"){         //in case of 'a' turn the LED on
//      digitalWrite(13, HIGH);  
//    }else if(inputString == "b"){   //incase of 'b' turn the LED off
//      digitalWrite(13, LOW);
//    }
//    inputString = "";
//  }
//}
