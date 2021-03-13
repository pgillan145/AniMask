
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
 
char clicker_history[HISTORY_LENGTH];

void setup() {
  PGardLibSetup();
  RFClickerSetup(clicker_history);

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

uint32_t now = 0;

void loop() {
  now = millis();
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

  
  getClickerHistory(clicker_history);
    for (uint8_t i = 0 ; i < HISTORY_LENGTH; i++) {
      uint8_t ble_buttons = clicker_history[i];
      if (BUTTON1(ble_buttons)) {
#ifdef CEREAL
          Serial.println("right");
#endif
          addAnimation(red, sizeof(red)/sizeof(red[0]), 15, ANI_REPEAT);
        } 
        else {
        }
        if (BUTTON2(ble_buttons)) {
#ifdef CEREAL
          Serial.println("down");
#endif
          addAnimation(frown, sizeof(frown)/sizeof(frown[0]), 15, ANI_HOLD);
        }
        else {
        }
        
        if (BUTTON3(ble_buttons)) {
#ifdef CEREAL
          Serial.println("left");
#endif
          addAnimation(blue, sizeof(blue)/sizeof(blue[0]), 15, ANI_REPEAT);
        }
        else {
        }
        if (BUTTON4(ble_buttons)) {
#ifdef CEREAL
          Serial.println("up");
#endif
          addAnimation(smile, sizeof(smile)/sizeof(smile[0]), 15, ANI_HOLD);
        }
        else {
        }
        matrix->show();
  }
}
