#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  430 // This is the 'maximum' pulse length count (out of 4096)

void setup() {
    Serial.begin(9600);
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  delay(10);
}

int angleToPulse(int angle){
    int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
//    Serial.print("Angle: ");Serial.print(angle);
//    Serial.print(" Pulse: ");Serial.print(pulse);
    return pulse;
}

void loop() {
  pwm.setPWM(0,0,angleToPulse(90));
  //delay(500);
}
