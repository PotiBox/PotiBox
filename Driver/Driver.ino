#include <SoftwareSerial.h>
#include <Servo.h>
#include "Debug.h"
#include "Music.h"
#include "Melodies.h"

const bool DEBUG = true;

SoftwareSerial mySerial(9, 11);
Music music = Music(7);
Servo servo;

const int SERVO_PIN = 10;
const int SERVO_SPIN = 1700;// counter clockwise
const int SERVO_STOP = 1500;

void setup() {
  Debug::setup(DEBUG);
  mySerial.begin(9600);
  servo.attach(SERVO_PIN);

  servo.write(SERVO_STOP);

  Debug::println("Starting PotiBox Driver");
}

void loop() {
  unsigned long currentTime = millis();

  if (mySerial.available()) {
    while (mySerial.available()) {
      char input = mySerial.read();

      if ('1' == input) {
        Debug::println("Bill inserted");
        music.setMelody(MELODY_BILL);
        servo.write(SERVO_SPIN);
      } else if ('2' == input) {
        Debug::println("Bill finished");
        music.setMelody(MELODY_NONE);
        servo.write(SERVO_STOP);
      } else if ('3' == input) {
        Debug::println("Coin inserted");
        music.setMelody(MELODY_COIN);
      }
    }
  }

  music.cycle(currentTime);
}
