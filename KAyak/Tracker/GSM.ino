SoftwareSerial SIM900(7, 8); // configure software serial port

boolean InitGSM()
{
    SIM900.begin(19200);
    CheckStatus();
    return true;

}


void CheckStatus(){
    SIM900.println("AT+CSQ");
    delay(100);
    ShowSerialData();
}


void ShowSerialData()
{
    while(SIM900.available()!=0)
        Serial.write(SIM900.read());
}





