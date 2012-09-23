/**
 *   API Frame Format
 *   ----------------------
 *   | Id | Len | Payload |
 *   ----------------------
 *
 *  API ID (1 Byte)
 *     0x81: RGB LED
 *
 *  Len (1 Byte, Max value 127)
 *
 *  Payload (Len Bytes)
 *
 */

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define BAUD_RATE 9600

#define SYNC 1
#define LEN 2
#define PAYLOAD 3
#define MAX_PAYLOAD 127

#define R_LED 6
#define G_LED 5
#define B_LED 3

class DataLink {
private:
  int state;
  int apiId;
  int len;
  int seq;
  int payload[MAX_PAYLOAD];
  
  void _RGB_LED(int R, int G, int B) {
    Serial.print('---');
    
    analogWrite(R_LED, R);
    analogWrite(G_LED, G);
    analogWrite(B_LED, B);
  }
  
  void _apiHandler() {
    switch (apiId) {
      case 1:
          _RGB_LED(payload[0], payload[1], payload[2]);
          break;
      default:
          break;
    }
  }
  
public:
  DataLink() {
    state = SYNC;
    apiId = 0;
    len = 0;
    seq = 0;
    for (int i=0; i<MAX_PAYLOAD; i++) {
      payload[i] = 0;
    }
  }
  
  void processChar(int c) {
    if (state == SYNC) {
      if (c > 0x7F) {
        state = LEN;
        apiId = c & 0x7F;
      }
    } else if (state == LEN) {
      if (c > 0x7F) {
        state = LEN;
        apiId = c & 0x7F;
      } else {
        state = PAYLOAD;
        len = c;
      }
    } else if (state == PAYLOAD) {
      payload[seq] = c;
      seq++;
      if (seq == len) {
        state = SYNC;
        seq = 0;
        _apiHandler();
      }
      
    } else {
      // should not reach here
    }
  }
    
};
