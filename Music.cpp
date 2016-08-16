#include "Arduino.h"
#include "Music.h"
#include "Melodies.h"
#include "Debug.h"

Music::Music(int speakerPin) {
  _speakerPin = speakerPin;
  _notePosition = 0;
}

void Music::begin() {
  pinMode(_speakerPin, OUTPUT);

  /*typedef std::pair<int, int> tt;
  typedef std::vector<tt> dd;

  dd items;  // you could typedef std::pair<char,int>
  items.push_back(tt(NOTE_C4, 1 ));
  items.push_back(tt(3, 2 ));
  items.push_back(tt(1, 3 ));*/
}

void Music::cycle(unsigned long currentTime) {
  // kill our playing if we are past our times
  if (_notePosition > (NOTES_COUNT - 1)) {
    //setMelody(MELODY_NONE);
    return;
  } else if (isEmptyMelody()) {
    return;
  }

  //int note = _melody[_notePosition][0];
  //int duration = _melody[_notePosition][1];
  
  /*unsigned long toneElapsedTime = currentTime - _toneTimer;

  if (toneElapsedTime > 500) {
    _toneTimer = currentTime;
    _notePosition++;
  }*/

  //printCurrentMelody();

  /*Debug::print("Note: ");
  Debug::print(note);
  Debug::print(" Duration: ");
  Debug::println(duration);*/

  //tone(_speakerPin, note);

  // This is blocking, use timers to make this non-blocking
  /*for (int i = 0; i < COIN_NOTES_COUNT; i++) {
    int noteDuration = 1000 / coinNoteDurations[i];
    int pauseBetweenNotes = noteDuration * 1.30;

    tone(SPEAKER_PIN, coinNote[i], noteDuration);
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
  }*/
}

bool Music::isEmptyMelody() {
  for (int i = 0; i < NOTES_COUNT; i++) {
    if (0 != _melody[i][0]) {
      return false;
    }
  }

  return true;
}

void Music::setMelody(const unsigned int melody[][2]) {
  Debug::println("!!!NEW MELODY!!!!");
  for (int i = 0; i < NOTES_COUNT; i++) {
    _melody[i][0] = melody[i][0];
    _melody[i][1] = melody[i][1];
  }

  _notePosition = 0;

  printCurrentMelody();
}

void Music::printCurrentMelody() {
  Debug::println("***current***");

  for (int i = 0; i < NOTES_COUNT; i++) {
    Debug::print("note: ");
    Debug::print(_melody[i][0]);
    Debug::print(" duration: ");
    Debug::println(_melody[i][1]);
  }
}

