const int buttonPin = 9;
const int ledPin = 13;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;



void setup(){
  Serial.begin(9600);
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,ledState);
}

void loop(){
  

  int reading = debounce();
  digitalWrite(ledPin,ledState);
  lastButtonState = reading;  


}


static inline int debounce() {
  int reading  = digitalRead(buttonPin);   

  if(reading != HIGH){
    lastDebounceTime = millis(); 
  }

  if((millis() - lastDebounceTime) > debounceDelay){
    if(reading != buttonState){
      buttonState = reading; 	


      if(buttonState == LOW){
        ledState=!ledState;    
      }
    }
  }

  Serial.println(reading);
  return reading;

}









