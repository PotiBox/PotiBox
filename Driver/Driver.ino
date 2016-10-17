#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Receiver setup done");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.println("mySerial.available");

    while (mySerial.available()) {
      Serial.write(mySerial.read());
    }

    Serial.println("---");
  }
}
