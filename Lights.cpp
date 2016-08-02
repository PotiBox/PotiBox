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

      if (timeSinceChange > 500) { // 500 = frequence of the changement of color
        Debug::println(timeSinceChange);
        Rainbowspin(20) ;
        _randomColorTimer = currentTime;
      }
    } else {
     // setColor(getColorFromInt(_color));
      Blink(500,3);
    }
  }else {
    // in case our timers went overflowing, we make sure we are OFF so we don't start random-coloring
    _color = OFF;
    setColor(off());
  }
}

// function blink blink for coin 
 void Lights::Blink(uint8_t wait, int nb) { // wait is the time of the blink ; nb is the number of blink
  blinkcolor = _color;
  for (int i =0; i < nb; i++) {
   
    
    setColor(getColorFromInt(blinkcolor)); // here is disgusting way of doing
    delay(wait);
    _color = OFF;
    setColor(off());
    delay(wait);
  }
 }
// Function spinning 
// Fill the dots one after the other with a color
/*
void Lights::spinning(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<_neoPixels.numPixels(); i++) {
    _neoPixels.setPixelColor(i-3, c/10);    _neoPixels.setPixelColor(i-1, c/2);
    _neoPixels.setPixelColor(i-5,0);    _neoPixels.setPixelColor(i-4, c/20);    _neoPixels.setPixelColor(i-2, c/4);
    _neoPixels.setPixelColor(i, c);
  _neoPixels.show();
  }  
    delay(wait);
}
*/

// function spinning with rainbow and which work !! 
void Lights::Rainbowspin(uint8_t wait) {
  uint16_t i, c,j;
j=5; // nunber of pixel on in the wave
    for(i=0; i< _neoPixels.numPixels(); i++) {
      for (c=0; c < _neoPixels.numPixels(); c++) {
        if (c < i +j) {
           _neoPixels.setPixelColor(c, Wheel(((i * 256 / _neoPixels.numPixels()) ) & 255));
        } else {
          _neoPixels.setPixelColor(c,0);
          
               }
        
      }
    
      
          _neoPixels.show();    delay(wait);
    }


  }


//Theatre-style crawling lights.
void Lights::theaterChase(uint32_t c, uint8_t wait) { // c = intensity, wait is time of the spin
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < _neoPixels.numPixels(); i=i+3) {
        _neoPixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      _neoPixels.show();

      delay(wait);

      for (uint16_t i=0; i < _neoPixels.numPixels(); i=i+3) {
        _neoPixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

uint32_t Lights::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return _neoPixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return _neoPixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return _neoPixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Slightly different, this makes the rainbow equally distributed throughout
void Lights::rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*2; j++) { // 2 cycles of all colors on wheel
    for(i=0; i< _neoPixels.numPixels(); i++) {
      _neoPixels.setPixelColor(i, Wheel(((i * 256 / _neoPixels.numPixels()) + j) & 255));
    }
    _neoPixels.show();
    delay(wait);
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

// function that set all random pixel
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

