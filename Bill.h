#ifndef Bill_h
#define Bill_h

#include "Arduino.h"
#include <Adafruit_TiCoServo.h>
#include <known_16bit_timers.h>

class Bill {
  public:
    Bill(int servoPin, int sensorPin, int servoIsOn);
    void begin();
    void cycle(unsigned long currentTime);
  private:
    static bool SERVO_IS_ON;
    static const int SENSOR_LIMIT = 70;
    static const int SERVO_SPIN = 1700;// counter clockwise
    static const int SERVO_STOP = 1500;

    Adafruit_TiCoServo _servo;
    int _servoPin;
    int _sensorPin;
    unsigned long _extraSpinTimer;
    bool _servoIsSpinning;
    bool _servoIsSpinningExtra;
};

#endif
