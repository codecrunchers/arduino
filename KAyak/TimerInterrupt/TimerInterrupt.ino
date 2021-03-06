
#define ledPin 7
int timer1_counter;
int ledState = HIGH;             // ledState used to set the LED

void setup()
{
    init_serial();
    pinMode(ledPin,OUTPUT);
    initTimer1();
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
    Serial.write("ISR Begin");

    TCNT1 = timer1_counter;   // preload timer
    ledToggle();
    Serial.write("ISR Complete");
}

void ledToggle(){
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
}


