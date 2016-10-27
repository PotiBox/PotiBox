#ifndef Debug_h
#define Debug_h

#include "Arduino.h"

class Debug {
  public:
    static void setup(bool isDebug);
    static void print(String out);
    static void println(String out);
    static void print(int out);
    static void println(int out);

    static bool IS_DEBUG;
};

#endif
