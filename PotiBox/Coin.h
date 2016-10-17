#ifndef Coin_h
#define Coin_h

#include "Arduino.h"

class Coin {
  public:
    Coin(int sensorPin);
    void cycle(unsigned long currentTime);
  private:
    static const int SENSOR_LIMIT = 200;

    int _sensorPin;
    bool _switched;
    unsigned long _switchTimer;
};

#endif
