#ifndef MyServo_h
#define MyServo_h
#include "Arduino.h" 
//#include <Adafruit_PWMServoDriver.h>
class MyServo {
public:
  MyServo(int sNum, int sMin, int sMax, int center); //sero number, max pulse length, min pulse length
  void begin();
  void moveToCenter();
  void update();
  int angleToPulse(int angle);
private:
  int _sNum;
  int _sMax;
  int _sMin;
  int _center;
  int current = 90; //starting position
  int target;
  int change = 10; //amount the servo can move in any direction, subtracted from _center

  int speed = 50;   //servo speed
  int delay = 1000;      // delay time
  unsigned long currentMillis = 0;  //Current time when called on
  unsigned long previousMillis = 0;            //Last time millis was recorded
  unsigned long posMillis    = 0;              //Last time target position was changed, updated at target position

};
#endif
