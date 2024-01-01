#include "Keyboard.h"

// gpio 2 for the button
const int buttonPin = 2;

// index array [0-9] to translate to ascii codes
// num[0] => 0
// num[9] => 0x39 = 9
const int num[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

bool GUARD = true;
bool run = false;

// The number should be in reverse, because of the carry propagating loop below
// e.g. 1234 -> 4321
int pins[] = {0, 0, 0, 0}; 

void pressSpacebar() {
    Keyboard.write(' ');
    delay(50);
}

void pressKey(int key) {
    Keyboard.press(key);
    delay(50);
    Keyboard.release(key);
    delay(50);
}

void writeKey(int key) {
    Keyboard.write(key);
    delay(50);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
  Keyboard.begin();
}

void carry() {
    int carry = 0;
    for (int i = 0; i < 4; ++i) {
  
      if (carry == 1) {
        ++pins[i];
        carry = 0;
      }
      if (pins[i] == 10) {
        pins[i] = 0;
        carry = 1;
      }
   }
}

void loop() {

  // IMPORTANT to use a button, otherwise the device becomes difficult to program through usb
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    run = true;
  }

  if (GUARD && run) {

    // One spacebar to wake the device
    pressSpacebar();
    delay(500);
    // Another spacebar to reach the pinscreen
    pressSpacebar();
    delay(500);      

    // Note: print in the reverse order
    writeKey(num[pins[3]]);
    writeKey(num[pins[2]]);
    writeKey(num[pins[1]]);
    writeKey(num[pins[0]]);
    pressKey(KEY_RETURN);

    // Backoff 29 + 0.5 + 0.5 = 30 [s]
    delay(29000);

    ++pins[0];
    carry();

    // End condition, should probably print something to the display matrix
    if (pins[0] == 2 && pins[1] == 9 && pins[2] == 9 && pins[3] == 9) {
      GUARD = false;
    }

  }
}



