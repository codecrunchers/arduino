

const int ledPin =  9;      // the number of the LED pin

void setup() {
  pinMode(ledPin, OUTPUT);      
}

void loop() {
  for (int i =0 ; i < 256; i++){
     analogWrite(ledPin, i);
     delay(10);
  }
  delay(2000);  
  for (int i ; i > 0; i--){
     analogWrite(ledPin, i);
     delay(10);
  }
  
   delay(2000);
  
}



