#ifndef AnimationBlink_h
#define AnimationBlink_h

#include "Arduino.h"
#include "AnimationInterface.h"

class AnimationBlink : public AnimationInterface {
  public:
    AnimationBlink();
    void cycle(unsigned long currentTime);
};

#endif
