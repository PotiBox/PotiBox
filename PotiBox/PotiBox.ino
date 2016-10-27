#include <NeoSWSerial.h>
#include "NeoPatterns.h"
#include "Debug.h"

#define STATUS_LIGHT_PIN 12

const bool DEBUG = false;

// bill sensor
const int BILL_SENSOR = A4;
// the bill sensor can jump slightly when a coin
const int BILL_SENSOR_LIMIT = 80;
unsigned long billTimer = 0;
bool billWasInserted = false;
bool billOnSensor = false;
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

  pinMode(STATUS_LIGHT_PIN, OUTPUT);
  analogWrite(STATUS_LIGHT_PIN, 255);
    
  neoPixels.begin();
  neoPixels.Off();

  // warmup photoresistors
  delay(1000);

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

  if (BILL_SENSOR_LIMIT < reading) {
    //Debug::print("Bill: ");
    //Debug::println(reading);

    if (!billOnSensor) {
      neoPixels.TheaterChase(neoPixels.Color(0, 0, 100), neoPixels.Color(0, 100, 100), 50, FORWARD);
      //neoPixels.Scanner(neoPixels.Color(0, 50, 50), 30);
      writeToDriver('1');
    }

    billWasInserted = true;
    billOnSensor = true;
  } else if (billWasInserted) {
    billOnSensor = false;

    if (!billIsExtraSpinning) {
      billIsExtraSpinning = true;
      billTimer = currentTime;
    } else if (5000 < (currentTime - billTimer)) {
      billWasInserted = false;
      billIsExtraSpinning = false;

      neoPixels.Off();
      writeToDriver('2');
    }
  }
}

void coinCycle() {
  int reading = analogRead(COIN_SENSOR);

  if (COIN_SENSOR_LIMIT < reading) {
    //Debug::print("Coin: ");
    //Debug::println(reading);

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
      //neoPixels.TheaterChase(neoPixels.Color(0, 0, 100), neoPixels.Color(0, 100, 100), 50, FORWARD);
      neoPixels.Scanner(neoPixels.Color(50, 50, 0), 50);
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

