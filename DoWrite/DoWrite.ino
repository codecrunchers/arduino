

const int ledPin =  13;      // theM <   number of the LED pin
int ledState = HIGH;   

void setup(){
  Serial.begin(57600);
  Serial.print(255);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop(){
  Serial.write(45); // send a byte with the value 45
  int bytesSent = Serial.print("hello\n"); //send the string “hello” and return the length of the string.
  delay(1000);                  // waits for a second
}

