


static const int RXPin = 5, TXPin = 6;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial gpsConn(RXPin, TXPin);

boolean InitGPS(){
    gpsConn.begin(GPSBaud);
    return true; 
}

void GPSLoop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsConn.available() > 0)
    if (gps.encode(gpsConn.read()))
      displayInfo();

  if (millis() > 10000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    return;
}
}


double lastLat = 0L;
double lastLng = 0L;
  
void displayInfo()
{
  double _lat = 0;
  double _lng = 0;
  
  
  
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(_lng, 6);

    if(lastLat !=0 ){   
      Serial.println();
      Serial.println();

   
      Serial.print(F("Distance from Prev {"));
      Serial.print(lastLat, 6);
      Serial.print(F(","));
      Serial.print(lastLng, 6);
      Serial.print(F("} is: "));      
      double distance =  TinyGPSPlus::distanceBetween(lastLat, lastLng, _lat, _lng);    
      Serial.print(distance, 6);
      Serial.println();
      Serial.println();

    }
    
    lastLat = gps.location.lat();
    lastLng = gps.location.lng();

    
  }
  else
  {
      Serial.print(gps.date.month());
      Serial.print(F("/"));
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}


