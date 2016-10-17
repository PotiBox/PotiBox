#ifndef Lights_h
#define Lights_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Lights {
  public:
    static const int OFF = -1;
    static const int RANDOM = 0;
    static const int RED = 1;
    static const int GREEN = 2;
    static const int BLUE = 3;
    static const int YELLOW = 4;
    static const int TURQUOISE = 5;
    static const int PURPLE = 6;
    static const int WHITE = 7;

    Lights(int pixelCount, int pin);
    void begin();
    void cycle(unsigned long currentTime);
    void animate(unsigned long currentTime, int milliseconds, int color);
    void setColor(uint32_t *color);
    uint32_t* getColorFromInt(int color);
    void setRandomColors();

    // colors
    uint32_t* off();
    uint32_t* randomColor();
    uint32_t* red();
    uint32_t* green();
    uint32_t* blue();
    uint32_t* yellow();
    uint32_t* turquoise();
    uint32_t* purple();
    uint32_t* white();
  private:
    int _pixelCount;
    Adafruit_NeoPixel _neoPixels;
    unsigned long _animateTimer;
    unsigned long _randomColorTimer;
    int _color;
};

#endif
