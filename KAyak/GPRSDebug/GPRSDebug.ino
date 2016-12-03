#include <SoftwareSerial.h> 
#include <GSM_Shield.h>

#define DEBUG_LED_ENABLED 1
#define DEBUG_PRINT 1




//**************************************************************************
char number[]="00353860484840";  //Destination number 
char text[]="hello world";  //SMS to send
byte type_sms=SMS_UNREAD;      //Type of SMS
byte del_sms=0;                //0: No deleting sms - 1: Deleting SMS
//**************************************************************************

GSM gsm;
char sms_rx[122]; //Received text SMS
//int inByte=0;    //Number of byte received on serial port
char number_incoming[20];
int call;
int error;


void setup() 
{
    Serial.begin(9600);
    Serial.println("system startup"); 
    gsm.TurnOn(9600);          //module power on
    gsm.InitParam(PARAM_SET_1);//configure the module  
    gsm.Echo(0);               //enable AT echo 
    Serial.println("Press s  to send text message");
}


void loop()
{
    char inSerial[5];
    int i=0;
    delay(2000);
    Check_SMS();

    if (Serial.available() > 0)
    {
        while (Serial.available() > 0) {
            inSerial[i]=(Serial.read());
            i++;
        }
        inSerial[i]='\0';
        Serial.print("Received ");
        Serial.println(inSerial);
        Check_Protocol(inSerial);
    }
}

void Check_Protocol(String inStr)
{   
    Serial.print("Command: ");
    Serial.println(inStr);

    Serial.println("Check_Protocol");

    switch (inStr[0])
    {
        case 's': 
            Serial.print("Send SMS to ");
            Serial.println(number);
            error=gsm.SendSMS(number,text);  
            switch(error){
                case 0:
                    Serial.println("SMS Not Sent after 3 Attempts\n");
                    break;
                case  1:
                    Serial.println("Sent");
                    break;
                case  -1:
                    Serial.println("CLS Not Free");
                    break;
                case  -2:
                    Serial.println("GSM Module Did Not Answer");
                    break;
                case  -3:
                    Serial.println("GSM Module replied ERROR");
                    break;
                default:
                    Serial.println("Unknown Response from SendSMS");
            }
            break;
        default:
            Serial.println("N/A");
    }

    Serial.print("Sleeping");
    delay(1500);
    return;
}


void Check_SMS()  //Check if there is an sms 'type_sms'
{
    Serial.println("Checking for SMS ");

    char pos_sms_rx;
    pos_sms_rx=gsm.IsSMSPresent(type_sms);

    if (pos_sms_rx > 0) {
        gsm.GetSMS(pos_sms_rx,number_incoming,sms_rx,120);
        Serial.print("Received SMS from ");
        Serial.print(number_incoming);
        Serial.print("(sim position: ");
        Serial.print(word(pos_sms_rx));
        Serial.println(")");
        Serial.println(sms_rx);
        if (del_sms==1)  //If 'del_sms' is 1, i delete sms 
        {
            error=gsm.DeleteSMS(pos_sms_rx);
            if (error==1)Serial.println("SMS deleted");      
            else Serial.println("SMS not deleted");
        }
    }
    else if(pos_sms_rx  == 0){
        Serial.print("No SMS Available ");
    }
    else if(pos_sms_rx  == -1){
        Serial.print("Comm Line Error ");
    }else if(pos_sms_rx  == -2){
        Serial.print("Received Error Checking SMS: ");
    }
    else {
        Serial.println("WTF");
    }

    Serial.println(word(pos_sms_rx));

    return;
}










