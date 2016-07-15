#include "Arduino.h"
#include "Debug.h"
#include "Bill.h"
#include "Player.h"

bool Bill::SERVO_IS_ON;

Bill::Bill(int servoPin, int sensorPin, int servoIsOn) {
  _servoPin = servoPin;
  _sensorPin = sensorPin;

  _extraSpinTimer = 0;
  _servoIsSpinning = false;
  _servoIsSpinningExtra = false;

  Bill::SERVO_IS_ON = servoIsOn;
}

void Bill::begin() {
  if (Bill::SERVO_IS_ON) {
    _servo.attach(_servoPin);
    _servo.write(Bill::SERVO_STOP);
  }
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
    _servoIsSpinning = true;

    if (Bill::SERVO_IS_ON) {
      _servo.write(Bill::SERVO_SPIN);
      Player::billInserted();
    }

    // notify our player
    //Player::billInserted();
  } else if (_servoIsSpinning) {
    if (!this->_servoIsSpinningExtra) {
      _servoIsSpinningExtra = true;
      _extraSpinTimer = currentTime;

      // notify our player
      Player::billFinished();
    } else if (5000 < (currentTime - _extraSpinTimer)) {
      _servoIsSpinning = false;
      _servoIsSpinningExtra = false;
    }
  } else {
    if (Bill::SERVO_IS_ON) {
      _servo.write(Bill::SERVO_STOP);
    }
  }
}
