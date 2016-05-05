#include <Servo.h> 

Servo myservo;  // create

const int ledPin =  9;      // theM <   number of the LED pin

void setup() {
  Serial.begin(9600); 
  myservo.attach(ledPin);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
  int curPos = myservo.read();
  if(curPos > 0)
    for(int i=curPos;i>0;i--){
      writeAndWait(i);

    }
  else{
    for(int i=0;i<180;i++){
      writeAndWait(i);
    }
  } 

  printData(myservo.read());

}


void writeAndWait(int offset){
  myservo.write(offset);
  delay(15);
}


void printData(int curPos){
  Serial.print("Reading Value:\t"); 
  Serial.print(curPos,DEC); 
  Serial.print("\n");   
}




