
//===================================================== ПОДЛКЮЧЕНИЕ БИБЛИОТЕКИ И СОЗДАНИЕ КОНСТАНТ ДЛЯ GPS МОДУЛЯ =====================================================
const uint8_t pinRX = 6;
const uint8_t pinTX = 5;
#include <iarduino_GPS_NMEA.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

//===================================================== ПОДЛКЮЧЕНИЕ БИБЛИОТЕКИ И СОЗДАНИЕ КОНСТАНТ ДЛЯ SD КАРТЫ =====================================================
const int chipSelect = 4;

iarduino_GPS_NMEA gps;
SoftwareSerial    SerialGPS(pinRX, pinTX);

//===================================================== ПОДЛКЮЧЕНИЕ БИБЛИОТЕКИ И СОЗДАНИЕ КОНСТАНТ ДЛЯ HTU21D =====================================================
#include <GyverHTU21D.h>
GyverHTU21D htu;

void setup() {


//===================================================== ИНИЦИЛИЗАЦИЯ GPS =====================================================
  Serial.begin(9600);
  SerialGPS.begin(9600);
  gps.begin(SerialGPS);


//===================================================== ИНИЦИЛИЗАЦИЯ SD КАРТЫ =====================================================
  while (!Serial) {
    ;
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    setup();
  }
  Serial.println("card initialized.");

  
//===================================================== ИНИЦИЛИЗАЦИЯ ДАТЧИКА HTU21D =====================================================
  htu.begin();

}


void loop() {


//===================================================== ОПРОС ДАТЧИКОВ И ЗАПИСЬ ДАННЫХ НА SD КАРТУ =====================================================
  gps.read();
  if ((!gps.errPos) && (htu.readTick())) {

    String dataString = "DATA: " + String(gps.latitude, 6) + " " + String(gps.longitude, 6) + " " + String(gps.Hours) + ":" + String(gps.minutes) + ":" + String(gps.seconds) + " " + String(gps.speed) + " " + String(htu.getTemperature(), 1) + " " + String(htu.getHumidity(), 1);
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
