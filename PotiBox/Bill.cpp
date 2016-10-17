#include "Arduino.h"
#include "Debug.h"
#include "Bill.h"
#include "Player.h"

Bill::Bill(int sensorPin) {
  _sensorPin = sensorPin;

  _billTimer = 0;
  _billWasInserted = false;
  _isExtraSpinning = false;
}

void Bill::cycle(unsigned long currentTime) {
  int reading = analogRead(_sensorPin);

  /*
   * 1) If we sense that it comes in, start spinning
   * 2) Spin until we notice that we have gone the whole way
   * 3) Spin for 2 more seconds to ensure the bill is fully though
   */

  //Debug::print("Bill: ");
  //Debug::println(reading);

  if (Bill::SENSOR_LIMIT < reading) {
    _billWasInserted = true;

    Player::billInserted();
  } else if (_billWasInserted) {
    if (!_isExtraSpinning) {
      _isExtraSpinning = true;
      _billTimer = currentTime;

      // notify our player
      Player::billFinished();
    } else if (5000 < (currentTime - _billTimer)) {
      _billWasInserted = false;
      _isExtraSpinning = false;
    }
  }
}
