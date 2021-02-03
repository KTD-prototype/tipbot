// reference:http://akiracing.com/2017/12/18/arduino_drone_motordrive/

#include <Servo.h>

const int throttle_max = 2000; //maximum width of the PWM
const int throttle_min = 1000; //minimum width of the PWM

Servo throttle; //generate the instance of the Servo with name "throttle"

int level = 0; //value of the motor output (width of the PWM(microsec))

int lowpower_pin = 5; //switch to drive motor in low mode
int highpower_pin = 7; //switch to drive motor in high mode


void setup() {
  Serial.begin(115200); //begin serial com with host PC

  pinMode(lowpower_pin, INPUT);
  pinMode(highpower_pin, INPUT);

  // ESC initialization process
  throttle.attach(9); //set the pin#9 as a PWM output
  level = throttle_min;
  throttle.writeMicroseconds(level); //set the throttle as minimum
  delay(2000);
  // initialization end
}

void loop() {
  int val1 = digitalRead(lowpower_pin); //read whether the switch#1 is ON
  int val2 = digitalRead(highpower_pin); //read whether the switch#2 is ON

  int sum = val2 * 2 + val1; //neither is off:0, #1 is on:1, #2 is on:2, eather is on:3
  level = 1000 + sum * 100; //set the width of the PWM accordingly (1000 ~ 1300)
  //  Serial.println(sum);
  throttle.writeMicroseconds(level); //drive motor
  Serial.println(level); //print drive motor level
}
