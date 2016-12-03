#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // configure software serial port

void InitGSM()
{
    boolean ready = SIM900.begin(19200);
    if(ready) debug_print("GSM Ready");
    return ready;
}


void execute_command(String cmd){
    debug_print("Executing",cmd);
    SIM900.println(cmd);
}



String read(){
    char inSerial[255]{'\0'};
    int i  = 0;
    if (Serial.available() > 0 ) {
        while (Serial.available() > 0)  {
            inSerial[i]=(Serial.read());
            i++;
        }
        inSerial[i]='\0';
        Serial.print("Received ");
        Serial.println(inSerial);
    }else{
        debug_print("No data received ","");
    }

    return inSerial;
}
