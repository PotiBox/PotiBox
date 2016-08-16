#ifndef Music_h
#define Music_h

#include "Arduino.h"
#include "Melodies.h"

class Music {
  public:
    Music(int speakerPin);
    void begin();
    void cycle(unsigned long currentTime);
    void setMelody(const unsigned int melody[][2]);
  private:
    int _speakerPin;
    unsigned long _toneTimer;
    unsigned int _notePosition;
    unsigned int _melody[10][2];

    bool isEmptyMelody();
    void printCurrentMelody();
};

#endif
