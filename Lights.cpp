#include "Arduino.h"
#include "Debug.h"
#include "Lights.h"

Lights::Lights(int pixelCount, int pin) {
  _pixelCount = pixelCount;

  _neoPixels = Adafruit_NeoPixel(_pixelCount, pin, NEO_GRB + NEO_KHZ800);

  _animateTimer = 0;
  _randomColorTimer = 0;
  _color = OFF;
}

void Lights::begin() {
  _neoPixels.begin();

  setColor(off());
}

void Lights::cycle(unsigned long currentTime) {
  if (currentTime < _animateTimer) {
    if (_color == RANDOM) {
      unsigned long timeSinceChange = currentTime - _randomColorTimer;

      if (timeSinceChange > 500) {
        Debug::println(timeSinceChange);
        setRandomColors();
        _randomColorTimer = currentTime;
      }
    } else {
      setColor(getColorFromInt(_color));
    }
  } else {
    // in case our timers went overflowing, we make sure we are OFF so we don't start random-coloring
    _color = OFF;
    setColor(off());
  }
}

void Lights::animate(unsigned long currentTime, int milliseconds, int color) {
  _animateTimer = currentTime + milliseconds;
  _color = color;
}

void Lights::setColor(uint32_t *color) {
  if (color[0] != 0 || color[1] != 0 || color[2] != 0) {
    Debug::println("setColor");
  }
  for (int i = 0; i < _pixelCount; i++) {
    _neoPixels.setPixelColor(i, _neoPixels.Color(color[0], color[1], color[2]));
  }

  _neoPixels.show();
}

void Lights::setRandomColors() {
  Debug::println("setRandomColors");
  uint32_t *color;
  for (int i = 0; i < _pixelCount; i++) {
    color = randomColor();
    _neoPixels.setPixelColor(i, _neoPixels.Color(color[0], color[1], color[2]));
  }

  _neoPixels.show();
}

uint32_t* Lights::getColorFromInt(int color) {
  switch (color) {
    case RED:
      return red();
    case GREEN:
      return green();
    case BLUE:
      return blue();
    case YELLOW:
      return yellow();
    case TURQUOISE:
      return turquoise();
    case PURPLE:
      return purple();
    case WHITE:
      return white();
    default:
      return off();
  }
}

uint32_t* Lights::off() {
  static uint32_t color[3] = {0, 0, 0};
  return color;
}

uint32_t * Lights::randomColor() {
  int color = random(1, 7);
  return getColorFromInt(color);
}

uint32_t* Lights::red() {
  static uint32_t color[3] = {100, 0, 0};
  return color;
}

uint32_t* Lights::green() {
  static uint32_t color[3] = {0, 100, 0};
  return color;
}

uint32_t* Lights::blue() {
  static uint32_t color[3] = {0, 0, 100};
  return color;
}

uint32_t* Lights::yellow() {
  static uint32_t color[3] = {100, 100, 0};
  return color;
}

uint32_t* Lights::turquoise() {
  static uint32_t color[3] = {0, 100, 100};
  return color;
}

uint32_t* Lights::purple() {
  static uint32_t color[3] = {100, 0, 100};
  return color;
}

uint32_t* Lights::white() {
  static uint32_t color[3] = {100, 100, 100};
  return color;
}

