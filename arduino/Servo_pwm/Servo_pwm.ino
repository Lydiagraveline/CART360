#include "MyServo.h"

//MyServo servo1(0, 140, 500); //pin, min, max
//MyServo servo2(1, 95, 430); //
#define NUM_SERVOS 16

MyServo servos[] = //{MyServo(0,150,600,90),MyServo(0,150,600,90) };
  
  {      //(pin, min, max, center)...
         //pan, tilt...
    MyServo(0, 140, 500, 90), MyServo(1, 100, 430, 80), 
    MyServo(2, 150, 600, 85), MyServo(3, 150, 505, 80), 
    MyServo(4, 150, 550, 75), MyServo(5, 150, 500, 105),
    MyServo(6, 100, 500, 90), MyServo(7, 100, 500, 90), 
    MyServo(8, 100, 490, 80), MyServo(9, 140, 490, 90), 
    MyServo(10, 100, 500, 70), MyServo(11, 100, 540, 90),
    MyServo(12, 95, 500, 100), //no tilt
    MyServo(13, 100, 500, 90), MyServo(14, 100, 500, 90),
    MyServo(15, 100, 500, 90) //no tilt
    };

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  140//95//140 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 500//430 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// servo # counter
//uint8_t servonum = 0;

const int MOTION_SENSOR_PIN = 12; // Arduino pin connected to motion sensor's pin
int state;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LEDS //
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#ifdef ESP32
// Cannot use 6 as output for ESP. Pins 6-11 are connected to SPI flash. Use 16 instead.
#define LED_PIN    16
#else
#define LED_PIN    6
#endif

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 100

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); // initialize serial
  pinMode(MOTION_SENSOR_PIN, INPUT); // set arduino pin to input mode
  
  for (int i=0; i < NUM_SERVOS; i++){  // start the servo objects
    servos[i].begin();
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//LEDS
      // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}

void loop() {
  state = digitalRead(MOTION_SENSOR_PIN);
  int angle;
  if(state == 1){
    //Serial.println("Somebody is in this area!");
    for (int i=0; i < NUM_SERVOS; i++){
    servos[i].moveToCenter();
    }
  }
  else if(state == 0){
 // Serial.println("No one!");
  angle = 0;
   for (int i=0; i < NUM_SERVOS; i++){
   servos[i].update();
    }
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LEDS //
//    for(int i=0; i<LED_COUNT; i++) { // For each pixel...
//
//    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
//    // Here we're using a moderately bright green color:
//    strip.setPixelColor(i, strip.Color(0, 150, 0));
//
//    strip.show();   // Send the updated pixel colors to the hardware.
//
//    strip.setBrightness(10);

//    delay(500); // Pause before next pass through loop

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //}


//servos[0].update(0);
  
//  servo1.update(90); //angle
//  servo2.update(90);
//  pwm.setPWM(0, 0, angleToPulse(90)); 

       //pwm.setPWM(0,0,SERVOMIN); 
       //delay(500);
       //pwm.setPWM(0,0,SERVOMAX);
       //delay(500);
       
  //  delay(500);
}
