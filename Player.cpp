#include "Arduino.h"
#include "Debug.h"
#include "Player.h"

byte Player::CURRENT_ANIM = Player::ANIM_NONE;

Player::Player(int pixelCount, int lightsPin, int speakerPin) :
  _lights(new Lights(pixelCount, lightsPin)) {
}

void Player::begin() {
  _lights->begin();
}

void Player::cycle(unsigned long currentTime) {
  switch (Player::CURRENT_ANIM) {
    case Player::ANIM_NONE:
      break;
    case Player::ANIM_BILL:
      _lights->animate(currentTime, 3000, Lights::RANDOM);
      break;
    case Player::ANIM_COIN:
      _lights->animate(currentTime, 500, Lights::BLUE); 
      break;
  }

  _lights->cycle(currentTime);

  Player::CURRENT_ANIM = Player::ANIM_NONE;
}

void Player::billInserted() {
  Player::CURRENT_ANIM = Player::ANIM_BILL;
}

void Player::billFinished() {
  Player::CURRENT_ANIM = Player::ANIM_NONE;
}

void Player::coinInserted() {
  Player::CURRENT_ANIM = Player::ANIM_COIN;
}
