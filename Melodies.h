#ifndef Melodies_h
#define Melodies_h

#include "Arduino.h"
#include "Notes.h"

#define NOTES_COUNT 10

const int MELODY_NONE[NOTES_COUNT][2] PROGMEM = {
  {0, 0}
};

const int MELODY_BILL[NOTES_COUNT][2] PROGMEM = {
  {0, 0}
};

const int MELODY_COIN[NOTES_COUNT][2] PROGMEM = {
  {NOTE_C4, 4},
  {NOTE_G3, 8},
  {NOTE_G3, 8},
  {NOTE_A3, 4},
  {NOTE_G3, 4},
  {NOTE_NONE, 4},
  {NOTE_B3, 4},
  {NOTE_C4, 4},
  {0, 0},
  {0, 0},
};

#endif

