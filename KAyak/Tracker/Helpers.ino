#define DEBUG 1

void InitSerial(){
    Serial.begin(19200);
    debug_print("Serial Ready @ 19200");
}


void debug_print(String msg){
#ifdef DEBUG
    Serial.print(F(">>"));
    Serial.println(msg);
    Serial.println("");
#endif
}




