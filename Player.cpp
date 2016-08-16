#include "Arduino.h"
#include "Debug.h"
#include "Player.h"
#include "Melodies.h"

byte Player::CURRENT_ANIM = Player::ANIM_NONE;

Player::Player(int pixelCount, int lightsPin, int speakerPin) :
  _lights(new Lights(pixelCount, lightsPin)),
  _music(new Music(speakerPin)) {
}

void Player::begin() {
  _lights->begin();
  _music->begin();
}

void Player::cycle(unsigned long currentTime) {
  switch (Player::CURRENT_ANIM) {
    case Player::ANIM_NONE:
      break;
    case Player::ANIM_BILL:
      Debug::println("Player: Bill");

      _lights->animate(currentTime, 5000, Lights::RANDOM);
      //_music->setMelody(&MELODY_BILL);
      break;
    case Player::ANIM_COIN:
      Debug::println("Player: Coin");

      _lights->animate(currentTime, 2000, Lights::YELLOW);
      //_music->setMelody(MELODY_COIN);
      break;
  }

  _lights->cycle(currentTime);
  _music->cycle(currentTime);

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
