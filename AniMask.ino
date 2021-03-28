#define CEREAL

#define MASK
#define MATRIX_W        15           /* Size (columns) of entire matrix */
#define MATRIX_H        6           /* and rows */
#define MATRIX          6
#define MAX_BRIGHT      255
#define BLUETOOTH       

#include <PGardLib.h>     // https://github.com/pgillan145/PGardLib
#include <RFClickerLib.h> // https://github.com/pgillan145/RFClickerLib
#include "AniMask.h"
 
#define MODES 2

uint32_t now = 0;
int mode = 0;

void updateMenu() {
  switch(mode) {
    case 0:
      writeMenu("RIGHT|FROWN|LEFT|SMILE");
      break;
    case 1:
      writeMenu("COPS|--|--|--");
      break;
  }
}

void setup() {
  PGardLibSetup();
  RFClickerLibSetup("AniMask", RFClickerButtonClick);
  updateMenu();
  matrix->begin();
  matrix->setBrightness(128);
}

//int x    = matrix->width();
//int pass = 0;
int proximity = 0;
float temperature = 0.0;
float humidity = 0.0; 
int16_t speed = 60;
int8_t color = 0;

void loop() {
  now = millis();
  BLE.poll();
  doAnimations();  
  
  String input_str = serialInput(10);

  if (input_str) {
    char c = input_str.charAt(0);
    String s2 = input_str.substring(1);
    int value_int = s2.toInt();
    switch(c) {
      case 'w':
#ifdef CEREAL
        SPL("up");
#endif
        addAnimation(smile, sizeof(smile)/sizeof(smile[0]), 15, ANI_HOLD);
        break;
      case 'a':
#ifdef CEREAL
        SPL("left");
#endif
        addAnimation(blue, sizeof(blue)/sizeof(blue[0]), 15, ANI_REPEAT);
        break;
      case 's':
#ifdef CEREAL
        Serial.println("down");
#endif
        addAnimation(frown, sizeof(frown)/sizeof(frown[0]), 15, ANI_HOLD);
        break;
      case 'd':
#ifdef CEREAL
        SPL("right");
#endif
        addAnimation(red, sizeof(red)/sizeof(red[0]), 15, ANI_REPEAT);
        break;
      case '?':
        SP("FOO:");
        SPL(value_int);
        break;
    };
  };
}

void RFClickerButtonClick(BLEDevice central, BLECharacteristic characteristic) {
  byte ble_buttons = (characteristic.value())[0];
    
  switch(mode) {
    case 0:
      if (TSTBUTTON(ble_buttons, BUTTON1)) {
          SPL("right");
          addAnimation(red, sizeof(red)/sizeof(red[0]), 15, ANI_REPEAT);
        } 
        else {
        }
        if (TSTBUTTON(ble_buttons, BUTTON2)) {
          SPL("down");
          addAnimation(frown, sizeof(frown)/sizeof(frown[0]), 15, ANI_HOLD);
        }
        else {
        }
        
        if (TSTBUTTON(ble_buttons, BUTTON3)) {
          SPL("left");
          addAnimation(blue, sizeof(blue)/sizeof(blue[0]), 15, ANI_REPEAT);
        }
        else {
        }
        if (TSTBUTTON(ble_buttons, BUTTON4)) {
          SPL("up");
          addAnimation(smile, sizeof(smile)/sizeof(smile[0]), 15, ANI_HOLD);
        }
        else {
        }
        matrix->show();
        break;
    case 1:
      if (TSTBUTTON(ble_buttons, BUTTON1)) {
          SPL("right");
          addAnimation(red, sizeof(red)/sizeof(red[0]), 15, ANI_REPEAT);
          addAnimation(blue, sizeof(blue)/sizeof(blue[0]), 15, ANI_REPEAT);
        } 
        else {
        }
        if (TSTBUTTON(ble_buttons, BUTTON2)) {
          SPL("down");
          addAnimation(frown, sizeof(frown)/sizeof(frown[0]), 15, ANI_HOLD);
        }
        else {
        }
        if (TSTBUTTON(ble_buttons, BUTTON3)) {
        }
        else {
        }
        if (TSTBUTTON(ble_buttons, BUTTON4)) {
        }
        else {
        }
        matrix->show();
        break;
  } // switch(mode)

  if (TSTBUTTON(ble_buttons, BUTTON5)) {
    SPL("button5");
    mode++;
    if (mode >= MODES) {
      mode = 0;
    }
    updateMenu();
  }
  if (TSTBUTTON(ble_buttons, BUTTON6)) {
    SPL("button6");
    mode--;
    if (mode < 0) {
      mode = MODES-1;
    }
    updateMenu();
  }
}
