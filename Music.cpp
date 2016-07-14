#include "Arduino.h"
#include "Music.h"

void Music::setup(int speakerPin) {
  Music::SPEAKER_PIN = speakerPin;
  Music::IS_PLAYING = false;
}

void Music::cycle() {
  unsigned long currentTime = millis();

  // This is blocking, use timers to make this non-blocking
  /*for (int i = 0; i < COIN_NOTES_COUNT; i++) {
    int noteDuration = 1000 / coinNoteDurations[i];
    tone(SPEAKER_PIN, coinNote[i], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
  }
  */
}

void Music::setMusic(int count, int notes[], int durations[]) {
  Music::NOTES_COUNT = count;
  //Music::NOTES = notes;
  //Music::NOTES_DURATIONS = durations;
}

