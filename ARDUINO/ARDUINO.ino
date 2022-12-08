const uint8_t pinRX = 6;
const uint8_t pinTX = 5;
//
#include <iarduino_GPS_NMEA.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;

iarduino_GPS_NMEA gps;
SoftwareSerial    SerialGPS(pinRX, pinTX);

void setup() {

//===================================================== ИНИЦИЛИЗАЦИЯ GPS =====================================================
  Serial.begin(9600);
  SerialGPS.begin(9600);
  gps.begin(SerialGPS);



  while (!Serial) {
    ;
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}


void loop() {
  gps.read();
  if (!gps.errPos) {

    String dataString = "GPS: " + String(gps.latitude, 6) + " " + String(gps.longitude, 6) + ", " + String(gps.Hours) + ":" + String(gps.minutes) + ":" + String(gps.seconds) + ", " + String(gps.speed);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);


    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
    }
    else {
      Serial.println("error opening datalog.txt");
    }

  }


}
