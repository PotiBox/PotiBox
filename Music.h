#ifndef Music_h
#define Music_h

#include "Arduino.h"

class Music {
  public:
    static void setup(int speakerPin);
    static void cycle();
    static void setMusic(int count, int notes[], int durations[]);
  private:
    static int SPEAKER_PIN;
    static bool IS_PLAYING;
    static int NOTES_COUNT;
    //static int *NOTES[];
    //static int *NOTES_DURATIONS[];
};

#endif
