#ifndef Music_h
#define Music_h

#include "Arduino.h"
#include "Melodies.h"

class Music {
  public:
    Music(int speakerPin);
    void cycle(unsigned long currentTime);
    void setMelody(const int (*melody)[2]);
  private:
    int _speakerPin;
    unsigned long _toneTimer;
    unsigned int _notePosition;
    boolean _firstNotePlayed;
    const int (*_melody)[2];
    int _currentNote;
    int _currentDuration;
    bool _isPlaying;

    bool isEmptyMelody();
    bool isEndNote(int notePosition);
    void setCurrentNoteAndDuration(int notePosition);
    int getNoteAt(int notePosition);
    int getDurationAt(int notePosition);
};

#endif

