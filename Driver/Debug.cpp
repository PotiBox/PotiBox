#include "Arduino.h"
#include "Debug.h"

bool Debug::IS_DEBUG;

void Debug::setup(bool isDebug) {
  Debug::IS_DEBUG = isDebug;

  if (Debug::IS_DEBUG) {
    Serial.begin(9600);
  }
}

void Debug::print(String out) {
  if (Debug::IS_DEBUG) {
    Serial.print(out);
  }
}

void Debug::println(String out) {
  if (Debug::IS_DEBUG) {
    Serial.println(out);
  }
}

void Debug::print(int out) {
  if (Debug::IS_DEBUG) {
    Serial.print(out);
  }
}

void Debug::println(int out) {
  if (Debug::IS_DEBUG) {
    Serial.println(out);
  }
}

