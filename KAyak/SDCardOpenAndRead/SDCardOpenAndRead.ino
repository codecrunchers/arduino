#include <SPI.h>
#include <SD.h>

File root;
const uint8_t CLOCK_SELECT=10;

void setup()
{

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only #ifdef ?
    }
    Serial.begin(9600);

    Serial.print("Initializing SD card...");
    pinMode(CLOCK_SELECT, OUTPUT);

    if (!SD.begin(CLOCK_SELECT)) {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");

    root = SD.open("/");
    printDirectory(root, 0);
    Serial.println("done!");
}

void loop()
{
    // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
    while(true) {
        File entry =  dir.openNextFile();
        if (! entry) {
            break;
        }
        for (uint8_t i=0; i<numTabs; i++) {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
            printDirectory(entry, numTabs+1);
        } else {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}


void createFile() {

}

