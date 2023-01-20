#include <AFMotor.h>

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);
AF_DCMotor motor2(2);
AF_DCMotor motor1(1);
String input_bytes;

void setup() 
{
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  /*motor4.setSpeed(300);
  motor4.run(RELEASE);

  motor3.setSpeed(200);
  motor3.run(RELEASE);

  motor2.setSpeed(300);
  motor2.run(RELEASE);

  motor1.setSpeed(200);
  motor1.run(RELEASE);*/
}

void switchDir(String dir)
{
  if(dir.equals("straight")){
    motor4.run(FORWARD);
    motor3.run(FORWARD);
    motor2.run(FORWARD);
    motor1.run(FORWARD);
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
  uint8_t i;
  // switchDir("left");
//
//  for (i=0; i<255; i++) 
//  {
//    setSpeeds(i, i, i, i); 
//    delay(10);
//  }
 
//  // Now turn off motor
//  motor4.run(RELEASE);
//  motor3.run(RELEASE);
//  motor2.run(RELEASE);
//  motor1.run(RELEASE);
//  delay(100);
  if (Serial.available() > 0) {
    input_bytes = Serial.readStringUntil('\n');
    if (input_bytes == "forward") {
      // uint8_t i;
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
      Serial.write("go forward");
    }
    if (input_bytes == "backward") {
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
      Serial.write("go backward");
    }
    else {
      Serial.write("invalid input");
    }
  }
  motor4.run(RELEASE);
  motor3.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(RELEASE);
  delay(1000);
}