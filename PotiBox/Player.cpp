#include "Arduino.h"
#include "Debug.h"
#include "Player.h"

byte Player::CURRENT_ANIM = Player::ANIM_NONE;
SoftwareSerial *Player::_driverSerial = 0;

Player::Player(int pixelCount, int lightsPin, int txPin, int rxPin) {
  _lights = new Lights(pixelCount, lightsPin);
  Player::_driverSerial = new SoftwareSerial(txPin, rxPin);

  Player::_driverSerial->begin(9600);
}

void Player::begin() {
  _lights->begin();
}

void Player::cycle(unsigned long currentTime) {
  switch (Player::CURRENT_ANIM) {
    case Player::ANIM_NONE:
      break;
    case Player::ANIM_BILL:
      Debug::println("Player: Bill");

      _lights->animate(currentTime, 5000, Lights::RANDOM);
      break;
    case Player::ANIM_COIN:
      Debug::println("Player: Coin");

      _lights->animate(currentTime, 2000, Lights::YELLOW);
      break;
  }

  // TODO: This breaks music for some reason right now!!
  _lights->cycle(currentTime);

  Player::CURRENT_ANIM = Player::ANIM_NONE;
}

void Player::billInserted() {
  Player::CURRENT_ANIM = Player::ANIM_BILL;
  Player::_driverSerial->write("billstart");
}

void Player::billFinished() {
  Player::CURRENT_ANIM = Player::ANIM_NONE;
  Player::_driverSerial->write("billstop");
}

void Player::coinInserted() {
  Player::CURRENT_ANIM = Player::ANIM_COIN;
  Player::_driverSerial->write("coinstart");
}
