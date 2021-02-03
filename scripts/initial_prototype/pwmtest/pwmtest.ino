// reference:http://akiracing.com/2017/12/18/arduino_drone_motordrive/

#include <Servo.h>

const int throttle_max = 2000; //maximum width of the PWM
const int throttle_min = 1000; //minimum width of the PWM

Servo throttle;
int level;

void setup() {
  Serial.begin(115200);

  throttle.attach(9);

  level = throttle_min;
  throttle.writeMicroseconds(level); //set the throttle as minimum
  delay(1000);
}

void loop() {
  for (level = 1000; level <= 1200; level += 1) {
    throttle.writeMicroseconds(level);
    delay(20);
    Serial.println(level);
  }

  for (level = 1200; level >= 1000; level -= 1) {
    throttle.writeMicroseconds(level);
    delay(20);
    Serial.println(level);
  }

  delay(3000);
}
