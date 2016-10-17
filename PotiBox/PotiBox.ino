#include "Debug.h"
#include "Bill.h"
#include "Coin.h"
#include "Player.h"

#define STATUS_LIGHT_PIN 12

// make sure to switch this to true if you want Serial debugging
const boolean DEBUG = true;

unsigned long MILLIS = 0;

// coin class
Coin coinClass = Coin(A5);

// bill class
Bill billClass = Bill(A4);

// player class (45 pixels per side)
Player playerClass = Player(45, 13, 9, 11);

void setup() {
  Debug::setup(DEBUG);

  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  analogWrite(STATUS_LIGHT_PIN, 255);

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

