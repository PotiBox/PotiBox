#include <NeoSWSerial.h>
#include "NeoPatterns.h"
#include "Debug.h"

const bool DEBUG = true;

// bill sensor
const int BILL_SENSOR = A4;
const int BILL_SENSOR_LIMIT = 70;
unsigned long billTimer = 0;
bool billWasInserted = false;
bool billIsExtraSpinning = false;
    
// coin sensor
const int COIN_SENSOR = A5;
const int COIN_SENSOR_LIMIT = 200;
bool coinSwitched = false;
unsigned long coinTimer;

// lights
void lightsComplete();
NeoPatterns neoPixels(45, 13, NEO_GRB + NEO_KHZ800, &lightsComplete);

// software serial
NeoSWSerial driverSerial(9, 11);

unsigned long currentTime;

// Initialize everything and prepare to start
void setup() {
  Debug::setup(DEBUG);
  driverSerial.begin(9600);
    
  neoPixels.begin();
  neoPixels.Off();

  Debug::println("Starting PotiBox");
}

// Main loop
void loop() {
  currentTime = millis();
  
  neoPixels.Update();
  billCycle();
  coinCycle();
}

void billCycle() {
  int reading = analogRead(BILL_SENSOR);

  /*
   * 1) If we sense that it comes in, start spinning
   * 2) Spin until we notice that we have gone the whole way
   * 3) Spin for 2 more seconds to ensure the bill is fully though
   */

  //Serial.print("Bill: ");
  //Serial.println(reading);

  if (BILL_SENSOR_LIMIT < reading) {
    billWasInserted = true;

    Serial.println("write 1");
    writeToDriver('1');
  } else if (billWasInserted) {
    if (!billIsExtraSpinning) {
      billIsExtraSpinning = true;
      billTimer = currentTime;

      Serial.println("write 2");
      writeToDriver('2');
    } else if (5000 < (currentTime - billTimer)) {
      billWasInserted = false;
      billIsExtraSpinning = false;
    }
  }
}

void coinCycle() {
  int reading = analogRead(COIN_SENSOR);

  //Serial.print("Coin: ");
  //Serial.println(reading);

  if (COIN_SENSOR_LIMIT > reading) {
    coinSwitched = true;
  } else {
    // if it was pressed and now is open again
    // then we can assume that a coin was inserted
    // but only allow a coin to be inserted once
    // every 0.5 seconds
    unsigned long switchElapsedTime = currentTime - coinTimer;

    if (coinSwitched && switchElapsedTime > 500) {
      coinTimer = currentTime;

      // coin inserted
      neoPixels.Scanner(neoPixels.Color(50, 50, 0), 50);
      Serial.println("write 3");
      writeToDriver('3');
    }

    coinSwitched = false;
  }
}

void writeToDriver(char out) {
  Debug::print("Write out: ");
  Debug::println(out);

  driverSerial.write(out);
}

void lightsComplete() {
  neoPixels.Off();

  Debug::println("Done");
}

