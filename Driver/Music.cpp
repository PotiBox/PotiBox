#include "Arduino.h"
#include "Music.h"
#include "Melodies.h"

Music::Music(int speakerPin) {
  _speakerPin = speakerPin;
  _notePosition = 0;
  _firstNotePlayed = false;
  _isPlaying = false;

  setMelody(MELODY_NONE);
}

void Music::cycle(unsigned long currentTime) {
  _isPlaying = false;

  // kill our playing if we are past our times
  if (isEmptyMelody()) {
    return;
  } else if (_notePosition > (NOTES_COUNT - 1)) {
    setMelody(MELODY_NONE);
    return;
  }

  _isPlaying = true;

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
  return _melody[notePosition][0];
}

int Music::getDurationAt(int notePosition) {
  int duration = _melody[notePosition][1];

  if (0 == duration) {
    return 0;
  }

  return 1000 / duration;
}

void Music::setMelody(const int (*melody)[2]) {
  // only change if not playing something
  if (_isPlaying) {
    return;
  }

  noTone(_speakerPin);
  _melody = melody;
  _notePosition = 0;
  _firstNotePlayed = false;
  setCurrentNoteAndDuration(0);
}

void Music::printCurrentMelody() {
  Serial.println("***current***");

  for (int i = 0; i < NOTES_COUNT; i++) {
    Serial.print("note: ");
    Serial.print(getNoteAt(i));
    Serial.print(" duration: ");
    Serial.print(getDurationAt(i));
    Serial.print(" speakerPin: ");
    Serial.println(_speakerPin);
  }
}

