#include "Arduino.h"
#include "Music.h"
#include "Melodies.h"
#include "Debug.h"
#include "PROGMEM_read.h"

Music::Music(int speakerPin) {
  _speakerPin = speakerPin;
  _notePosition = 0;
  _firstNotePlayed = false;

  setMelody(MELODY_NONE);
}

void Music::begin() {
}

void Music::cycle(unsigned long currentTime) {
  // kill our playing if we are past our times
  if (isEmptyMelody()) {
    return;
  } else if (_notePosition > (NOTES_COUNT - 1)) {
    setMelody(MELODY_NONE);
    return;
  }

  unsigned long toneElapsedTime = currentTime - _toneTimer;

  if (!_firstNotePlayed) {
    noTone(_speakerPin);
    tone(_speakerPin, _currentNote, _currentDuration);

    _toneTimer = currentTime;
    _firstNotePlayed = true;
  } else if (toneElapsedTime > (_currentDuration * 1.3)) {
    noTone(_speakerPin);

    _toneTimer = currentTime;
    _notePosition++;
    setCurrentNoteAndDuration(_notePosition);

    if (isEndNote(_notePosition)) {
      return;
    }

    tone(_speakerPin, _currentNote, _currentDuration);
  }
}

bool Music::isEmptyMelody() {
  if (isEndNote(0)) {
    return true;
  }

  for (int i = 0; i < NOTES_COUNT; i++) {
    if (getDurationAt(i) > 0) {
      return false;
    }
  }

  return true;
}

bool Music::isEndNote(int notePosition) {
  return (getDurationAt(notePosition) <= 0);
}

void Music::setCurrentNoteAndDuration(int notePosition) {
  _currentNote = getNoteAt(notePosition);
  _currentDuration = getDurationAt(notePosition);
}

int Music::getNoteAt(int notePosition) {
  int item[2];
  PROGMEM_readAnything(&_melody[notePosition], item);

  return item[0];
}

int Music::getDurationAt(int notePosition) {
  int item[2];
  PROGMEM_readAnything(&_melody[notePosition], item);

  if (0 == item[1]) {
    return 0;
  }

  return 1000 / item[1];
}

void Music::setMelody(const int (*melody)[2]) {
  noTone(_speakerPin);
  _melody = melody;
  _notePosition = 0;
  _firstNotePlayed = false;
  setCurrentNoteAndDuration(0);
}

void Music::printCurrentMelody() {
  Debug::println("***current***");

  for (int i = 0; i < NOTES_COUNT; i++) {
    Debug::print("note: ");
    Debug::print(getNoteAt(i));
    Debug::print(" duration: ");
    Debug::print(getDurationAt(i));
    Debug::print(" speakerPin: ");
    Debug::println(_speakerPin);
  }
}

