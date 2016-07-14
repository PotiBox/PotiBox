#include "Debug.h"
#include "notes.h"
#include "Bill.h"
#include "Coin.h"
#include "Player.h"

const boolean DEBUG = true;

unsigned long MILLIS = 0;

// speaker variables
//const int SPEAKER_PIN = 8;

// coin class
Coin coinClass = Coin(A5);

//const int COIN_NOTES_COUNT = 8;
//int coinNote[COIN_NOTES_COUNT] = {
//  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
//};
//int coinNoteDurations[COIN_NOTES_COUNT] = {
//  4, 8, 8, 4, 4, 4, 4, 4
//};

// bill class
Bill billClass = Bill(10, A4, true);

// player class (45 pixels per side)
Player playerClass = Player(45, 13, 11);

void setup() {
  Debug::setup(DEBUG);

  pinMode(8, OUTPUT);

  billClass.begin();
  playerClass.begin();

  // wait a bit for our
  // photo resistors to warm up
  delay(1000);
}

void loop() {
  unsigned long currentTime = millis();
  
  coinClass.cycle(currentTime);
  billClass.cycle(currentTime);
  playerClass.cycle(currentTime);
}

