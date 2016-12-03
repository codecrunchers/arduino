#include <SPI.h>
#include <SD.h>

#define ledPin 7
int timer1_counter;
int counter = 0;             // ledState used to set the LED
const uint8_t CLOCK_SELECT=10;
File readme;


void setup()
{
    init_serial();
    init_sd();
    pinMode(ledPin,OUTPUT);
    initTimer1();
}


void init_sd(){
    Serial.print("Initializing SD card...");
    pinMode(CLOCK_SELECT, OUTPUT);

    if (!SD.begin(CLOCK_SELECT)) {
        Serial.println("sd card initialization failed!");
        return;
    }

    createFile();
//    readFile();


}


void initTimer1(){
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
    TCNT1 = timer1_counter;   // preload timer
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
    interrupts();             // enable all interrupts

}

void init_serial(){
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only #ifdef ?
    }
    Serial.begin(9600);
}

void loop()
{

}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
    Serial.write("ISR Begin\n");
    TCNT1 = timer1_counter;   // preload timer
    //Serial.println(digitalRead(ledPin));
    digitalWrite(ledPin,digitalRead(ledPin)^1);
    Serial.write("ISR Complete\n");
}

void readFile(){
    readme = SD.open("readme.txt");
    if (readme) {
        Serial.println("readme.txt:");

        // read from the file until there's nothing else in it:
        while (readme.available()) {
            Serial.write(readme.read());
        }
        // close the file:
        readme.close();
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening readme.txt");
    }
}


void createFile() {
    readme = SD.open("readme.txt", FILE_WRITE);
    if (readme) {
        Serial.print("Writing...");
        Serial.print("Wrote..");
        Serial.print(readme.write("Alan Ryan\n"));
        Serial.println(" chars");
        readme.flush();
        readme.close();
        Serial.println("done.");
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
}


