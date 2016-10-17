#ifndef Player_h
#define Player_h

#include <SoftwareSerial.h>

#include "Arduino.h"
#include "Lights.h"

class Player {
  public:
    static const byte ANIM_NONE = 0;
    static const byte ANIM_BILL = 1;
    static const byte ANIM_COIN = 2;

    static byte CURRENT_ANIM;

    Player(int pixelCount, int lightsPin, int txPin, int rxPin);
    void begin();
    void cycle(unsigned long currentTime);

    static void billInserted();
    static void billFinished();
    static void coinInserted();
  private:
    Lights *_lights;
    static SoftwareSerial *_driverSerial;
};

#endif
