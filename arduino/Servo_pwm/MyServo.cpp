#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "MyServo.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

MyServo::MyServo(int sNum, int sMin, int sMax, int center) {
  _sNum = sNum;
  _sMax = sMax;
  _sMin = sMin;
  _center = center;
}
 void MyServo::begin(){
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates //SERVO_FREQ)
  target = random(_center - change, _center + change);
   Serial.print("target = ");
  Serial.println(target);
  //Serial.println("begin!");
  }

  void MyServo::moveToCenter(){
    current = _center;
    pwm.setPWM(_sNum, 0, angleToPulse(current)); 
    Serial.println("Somebody is in this area!");
  }

  void MyServo::update() {
  currentMillis = millis();             
  if (currentMillis - posMillis >= delay) {   //delay for a bit when the servo reaches it's goal
     
      //update
      if (currentMillis - previousMillis >= speed) {       //Check to see if its time to move again
        previousMillis = millis();   

        //move
        if (current < target){
          current++;
        }
        else if (current > target){
          current--;
        }

        // when the servo reaches it's target position ...
        else if (current == target){
//        Serial.println("target reached");
        posMillis = currentMillis; //reset the delay
        delay = random(0, 2000);  //new random delay time
        target = random(_center - change, _center + change); //new random target
        speed = random (50, 80); //new random speed
       
//        Serial.print("delay = ");
//        Serial.println(delay); 
//        Serial.print("new speed = ");
//        Serial.println(speed); 
//        Serial.print("new target = ");
//        Serial.println(target);    
      } 
       pwm.setPWM(_sNum, 0, angleToPulse(current));
   
      } // if speed
    } //if delay
  } //update
  
//  void MyServo::update(){
//   
//     
//      if (millis() - previousMillis > delay)
//      {
//        previousMillis = millis();
//      if (current < target){
//        current++;
//      } 
//      else if (current > target){
//        current--;
//      }
//      else if (current == target){
//        Serial.println("target reached");
//        posMillis = currentMillis;
//        target = random(10, 175);
//        speed = random (20, 80);
//        delay = random(2000, 10000); 
//          
//        Serial.print("new speed = ");
//         Serial.println(speed); 
//        Serial.print("new target = ");
//        Serial.println(target);    
//      }
//       
//      }
//      pwm.setPWM(_sNum, 0, angleToPulse(current));
//  }

int MyServo::angleToPulse(int angle){
    int pulse = map(angle, 0, 180, _sMin, _sMax);
//    Serial.print("Angle: ");Serial.print(angle);
//    Serial.print(" Pulse: ");Serial.print(pulse);
    return pulse;
}
