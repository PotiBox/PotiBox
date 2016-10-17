#ifndef Bill_h
#define Bill_h

#include "Arduino.h"

class Bill {
  public:
    Bill(int sensorPin);
    void cycle(unsigned long currentTime);
  private:
    static const int SENSOR_LIMIT = 70;

    int _sensorPin;
    unsigned long _billTimer;
    bool _billWasInserted;
    bool _isExtraSpinning;
};

#endif
