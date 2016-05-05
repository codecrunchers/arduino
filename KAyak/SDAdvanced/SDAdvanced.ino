#include <FlexiTimer2.h>
#include "Fat16.h"
#include "SdCard.h"
#include "WString.h"


SdCard card;
Fat16 file;

boolean blinker;
boolean blinklogic;
int counter;
int counter1;
int tmpval;
int time;
//Digital Pin 3 (= Interrupt 1)
// 10k auf GRND
//Digital Pin 3 auf 10K
// Reed an 10K
//andere Seite Reed an 5V
boolean debug;

void setup(){
debug=false;
 pinMode(11, INPUT);
pinMode(13, OUTPUT);
Serial.begin(9600);

blinker = false;
blinklogic = true;
counter=0;
counter1=0;
tmpval = 0;
time = millis();
attachInterrupt(1,count,RISING);

FlexiTimer2::set(1000,report);
FlexiTimer2::start();

  if (!card.init()) error1("card.init");
 
  // initialize a FAT16 volume
  if (!Fat16::init(card)) error1("Fat16::init");
 
  // create a new file
  char name[] = "WIND0.00";
  for (uint8_t i = 0; i < 100; i++) {
    name[6] = i/10 + '0';
    name[7] = i%10 + '0';
    if (file.create(name)) break;
  }
  if (!file.isOpen()) error1("file.create");
  if(debug){
    Serial.print("Logging to: ");
    Serial.println(name);
  }
  //Header im File schreiben
  file.println("Umrundungen Windturbine");
 
   if (file.writeByteError || !file.sync()) {
     error1("write header");
   }
}

void error1(char *str){
 Serial.print("error ");
 Serial.println(str);
}

void report(){
 if(debug){
   Serial.print("Drehzahl: ");
   Serial.print(counter/2);
   Serial.print(", ");
   Serial.println(counter1/2);
 }
 counter = 0;
  

}

void count(){
//increase counter
counter++;
counter1++;
if((counter1/2)!=tmpval){
  /*Serial.print("tmpval: ");
  Serial.print(tmpval);
  Serial.print(", ");*/
  Serial.println(counter1/2);

}
tmpval = counter1/2;
 
}

void loop(){

 file.print((millis()/1000));
 file.print(";");
 file.println(counter1/2);
 delay(30);

 if (file.writeByteError) {
   error1("write data");
   blinklogic=false;
   //Serial.println("blinklogic false");
   }
 if (!file.sync()){
   error1("sync");
   blinklogic=false;
   if(debug){
     Serial.println("blinklogic false");
   }  
 }
 if(blinklogic){
   if(debug){  
     Serial.println("blinklogic high");
   }
   if(blinker==false){
      digitalWrite(13, HIGH);
     if(debug){  
        Serial.println("blinker high");
     }
      blinker=true;
    }else
    if(blinker==true){
      digitalWrite(13,LOW);
      if(debug){
        Serial.println("blinker low");
      }
      blinker=false;
    }
  else if(!blinklogic)digitalWrite(13,LOW);
 }
  Serial.println(counter1/2);
 delay(970);
 
 
}
