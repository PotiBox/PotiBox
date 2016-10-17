#include "Arduino.h"
#include "Debug.h"
#include "Coin.h"
#include "Player.h"

Coin::Coin(int sensorPin) {
  _sensorPin = sensorPin;

  _switched = false;
  _switchTimer = 0;
}

void Coin::cycle(unsigned long currentTime) {
  int reading = analogRead(_sensorPin);

  //Debug::print("Coin: ");
  //Debug::println(reading);

  if (Coin::SENSOR_LIMIT > reading) {
    _switched = true;
  } else {
    // if it was pressed and now is open again
    // then we can assume that a coin was inserted
    // but only allow a coin to be inserted once
    // every 0.5 seconds
    unsigned long switchElapsedTime = currentTime - _switchTimer;

    if (_switched && switchElapsedTime > 500) {
      _switchTimer = currentTime;

      Player::coinInserted();
    }

    _switched = false;
  }
}

