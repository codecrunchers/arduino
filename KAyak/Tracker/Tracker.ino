#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TinyGPS++.h>

void setup(){
    InitSerial();
    boolean ready = InitGPS();
    
    if(ready){
        debug_print("Ready");
        GPSLoop() ; //&& InitGPS() &&*/ InitGSM() && InitGPS() && InitSDCard();
    }


}


void loop()
{
    GPSLoop();
}

