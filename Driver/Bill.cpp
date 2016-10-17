#include "Arduino.h"
#include "Bill.h"

Bill::Bill(int servoPin) {
  _servoPin = servoPin;
}

void Bill::begin() {
  _servo.attach(_servoPin);
  _servo.write(Bill::SERVO_STOP);
}

void Bill::start() {
  _servo.write(Bill::SERVO_SPIN);
}

void Bill::stop() {
  _servo.write(Bill::SERVO_STOP);
}
