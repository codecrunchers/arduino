void setup(){
    InitSerial();
    boolean ready = InitSDCard() ; //&& InitGPS() &&*/ InitGSM() && InitGPS() && InitSDCard();
    if(ready){
        debug_print("Ready");
    }


}


void loop()
{
    GPSLoop();
}

