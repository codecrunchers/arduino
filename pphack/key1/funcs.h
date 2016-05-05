#include "Arduino.h"

int key0_state;
long lastDebounceTime = 0;
long debounceDelay = 50;
int lastButtonState = LOW;

static inline void foo(){
  Serial.println(9);

}

static inline int debounce(int state){
  int curState = state;
  if(curState!=lastButtonState){
    return 9;
  }
}
