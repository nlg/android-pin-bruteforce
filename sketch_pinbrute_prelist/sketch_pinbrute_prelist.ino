#include "Keyboard.h"

const int buttonPin = 2;          
const int num[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
bool GUARD = true;
bool run = false;


int pins10[][10] = {
// 10 pin
{3,1,4,1,5,9,2,6,5,4},
{3,3,3,3,3,3,3,3,3,3},
{7,8,9,4,5,6,1,2,3,0},
{1,2,3,4,5,6,7,8,9,1},
};


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

void enterPinscreen() {
    pressSpacebar();
    delay(500);
    pressSpacebar();
    delay(500);          
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    run = true;
  }

  if (GUARD && run) {

    size_t len_rows = sizeof(pins10)/sizeof(pins10[0]);
    size_t len_cols = sizeof(pins10[0])/sizeof(pins10[0][0]);

    for (int current_row = 0; current_row < len_rows; ++current_row) {
      enterPinscreen();
      
      for (int current_col = 0; current_col < len_cols; ++current_col) {
        int n = pins10[current_row][current_col];
        writeKey(num[n]);
      }

      pressKey(KEY_RETURN);
      delay(29000);
    }
    GUARD = false;
  }
}



