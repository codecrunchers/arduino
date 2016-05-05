#include "funcs.h"
const int key0_pin = 9;


void setup(){
  Serial.begin(9600);
  pinMode(key0_pin,INPUT);
}

void loop(){
  key0_state = debounce(digitalRead(key0_pin));   
  Serial.println(key0_state);
  delay(1);   
}


