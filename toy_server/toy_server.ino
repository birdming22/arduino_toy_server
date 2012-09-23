/**
 * Demonstrate sending a api packet to the Arduino.
 *
 * Run this sketch on the Arduino, and ToyController on Android.
 */

#include "DataLink.h"

DataLink dataLink;

void setup() {
  Serial.begin(BAUD_RATE);
  
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
}

void loop() {
  while (Serial.available() > 0) {
    dataLink.processChar(Serial.read());
  }
}
