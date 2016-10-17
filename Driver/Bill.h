#ifndef Bill_h
#define Bill_h

#include "Arduino.h"
#include <Servo.h>

class Bill {
  public:
    Bill(int servoPin);
    void begin();
    void start();
    void stop();
  private:
    static const int SERVO_SPIN = 1700;// counter clockwise
    static const int SERVO_STOP = 1500;

    Servo _servo;
    int _servoPin;
};

#endif
