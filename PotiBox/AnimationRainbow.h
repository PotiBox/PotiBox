#ifndef AnimationRainbow_h
#define AnimationRainbow_h

#include "Arduino.h"
#include "AnimationInterface.h"

class AnimationRainbow : public AnimationInterface {
  public:
    AnimationRainbow();
    void cycle(unsigned long currentTime);
};

#endif
