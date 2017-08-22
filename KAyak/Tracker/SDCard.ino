

const uint8_t CLOCK_SELECT=10;

boolean InitSDCard(){ 
    debug_print("Initializing SD card...");
    pinMode(CLOCK_SELECT, OUTPUT);

    int attempt = 0;
    while(!SD.begin(CLOCK_SELECT) && attempt < 3) {
        delay(1000);
        attempt++;
    }

    if (attempt==3) {
        debug_print("SD Card Initialization failed!");
        return false;
    }

    debug_print("initialization done.");

    return (boolean)createFile();
}

int createFile() {
    File readme = SD.open("readme.txt", FILE_WRITE);
    if (readme) {
        Serial.print("Writing...");
        Serial.print("Wrote..");
        Serial.print(readme.write("Alan Ryan"));
        Serial.println(" chars");
        readme.flush();
        readme.close();
        Serial.println("done.");
        return 1;
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
        return -1;
    }

    return -1;

}





