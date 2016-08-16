#ifndef Melodies_h
#define Melodies_h

#include "Arduino.h"
#include "Notes.h"

#define NOTES_COUNT 10

//const unsigned int MELODY_NONE[NOTES_COUNT][2] = {0};

//const unsigned int MELODY_BILL[NOTES_COUNT][2] = {0};

/*const unsigned int MELODY_COIN[NOTES_COUNT][2] = {
  {NOTE_C4, 5},
  {NOTE_G3, 10},
  {NOTE_G3, 10},
  {NOTE_A3, 5},
  {NOTE_G3, 5},
  {NOTE_NONE, 5},
  {NOTE_B3, 5},
  {NOTE_C4, 5},
  {0, 0},
  {0, 0},
};*/

#endif

/*
#ifndef Melodies_h
#define Melodies_h

#include "Arduino.h"
#include <StandardCplusplus.h>
#include <vector>

struct Note {
  int note;
  int duration;

  Note(int a, int b) : note(a), duration(b) {}
};

using Melody = std::vector<Note>;

//const int MAX_NOTES = 10;
//typedef const int Melody[MAX_NOTES][2];

extern const Melody MELODY_NONE;
extern const Melody MELODY_BILL;
extern const Melody MELODY_COIN;

#endif
*/
