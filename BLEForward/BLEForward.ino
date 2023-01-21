#include <AFMotor.h>

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);
AF_DCMotor motor2(2);
AF_DCMotor motor1(1);
char junk;
String inputString="";

void setup() 
{
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  motor4.setSpeed(200);
  motor4.run(RELEASE);

  motor3.setSpeed(200);
  motor3.run(RELEASE);

  motor2.setSpeed(200);
  motor2.run(RELEASE);

  motor1.setSpeed(200);
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
  uint8_t i;
  
  if (Serial.available() > 0) {
//    input_bytes = Serial.readStringUntil('\n');
//    {junk = Serial.read() ;}
        while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    { junk = Serial.read() ; }
    if (inputString == "f") {
      // Now change motor direction
      switchDir("forward");
      setSpeeds(255, 255, 255, 255);
      delay(1000);
    
      Serial.write("go forward");
     }
     
    }
    if (inputString == "b") {
      // Now change motor direction
       switchDir("backward");
       setSpeeds(255, 255, 255, 255);
       delay(1000);
     
      Serial.write("go backward");
    }
    if(inputString == "s") {
      switchDir("stop");
      Serial.write("stop");
    }
    if(inputString == "r"){
      switchDir("right");
      setSpeeds(255, 255, 255, 255);
      delay(1000);
      
      Serial.write("right");
    }
    if(inputString == "l") {
      switchDir("left");
      setSpeeds(255, 255, 255, 255);
      delay(1000);
      
      Serial.write("left");
    }
//    else {
//      Serial.write("invalid input");
      /* motor4.run(RELEASE);
      motor3.run(RELEASE);
      motor2.run(RELEASE);
      motor1.run(RELEASE);*/
//    }
  inputString = "";
  }
//  motor4.run(RELEASE);
//  motor3.run(RELEASE);
//  motor2.run(RELEASE);
//  motor1.run(RELEASE);
//  delay(1000);



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
