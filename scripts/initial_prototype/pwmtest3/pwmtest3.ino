// reference:http://akiracing.com/2017/12/18/arduino_drone_motordrive/

#include <Servo.h>

const int throttle_max = 2000; //maximum width of the PWM(msec)
const int throttle_min = 1000; //minimum width of the PWM(msec)

Servo throttle; //generate the instance of the Servo with name "throttle"

int level = 0; //value of the motor output (width of the PWM(microsec))

int lowpower_pin = 5; //switch to drive motor in low mode
int highpower_pin = 7; //switch to drive motor in high mode


void setup() {
  Serial.begin(115200); //begin serial com with host PC

  pinMode(lowpower_pin, INPUT);
  pinMode(highpower_pin, INPUT);

  throttle.attach(9); //set the pin#9 as a PWM output
  //  esc_calibration(); // ESC calibration process (only needed at 1st time just after purchasing new ESC ? )
}

void loop() {
  int val1 = digitalRead(lowpower_pin); //read whether the switch#1 is ON
  int val2 = digitalRead(highpower_pin); //read whether the switch#2 is ON

  int sum = val2 * 2 + val1; //neither is off:0, #1 is on:1, #2 is on:2, eather is on:3
  level = 1000 + sum * 200; //set the width of the PWM accordingly (1000 ~ 1300)
  //  Serial.println(sum);
  throttle.writeMicroseconds(level); //drive motor
  Serial.println(level); //print drive motor level
}

void esc_calibration() {
  //step 1 : disconnect your battery
  //step 2 : set the throttle to maximum
  throttle.writeMicroseconds(throttle_max); //set the throttle as maximum
  //step 3 : connect your battery (keeping throttle as maximum)
  delay(5000);
  //beeps can be hear 3 times (di da di)
  //step 4 : wait more than 1 seconds
  //short beep can be hear 1 time (di)
  //step 5 : set the throttle to minimum
  throttle.writeMicroseconds(throttle_min); //set the throttle as minimum
  //beeps can be hear 2 times (di di)
  delay(5000);
  // long beep will can be hear 1 time (if you hear short beep, it might be failed to calibrate)
  //step 6 : disconnect your battery
  // calibration end
}
