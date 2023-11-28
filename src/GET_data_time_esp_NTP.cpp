// фукнція відправки запиту з плати нано на модуль ESP для отримання точного часу
#pragma once
#include "main.h"
const byte timeRequestCommand = 1; // Команда запиту на отримання часу

struct DateTime {
  uint8_t second;
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
};

DateTime receivedTime;
// Надіслати запит ESP8266 на отримання точного часу
void Get_data_time_ESP8266() {
  
  Wire.beginTransmission(espAddress);
  byte error = Wire.endTransmission();
  
  if(error==0)
  
  Wire.beginTransmission(espAddress);// шукаємо модуль ESP8266
  Wire.write(timeRequestCommand);
  Wire.endTransmission();

  delay(3000);  // Додано затримку для дочекання передачі даних

 if (Wire.available()) {
    byte deviceAddress = Wire.read();
    if (deviceAddress == espAddress) {
       
      DateTime receivedTime;
      Wire.readBytes((uint8_t*)&receivedTime, sizeof(receivedTime));
     
       
     // Serial.println("Received time from ESP8266: " + String(receivedTime.year()) + "-" + String(receivedTime.month()) + "-" + String(receivedTime.day()) + " " + String(receivedTime.hour()) + ":" + String(receivedTime.minute()) + ":" + String(receivedTime.second()));
      // Запис точного часу на модуль RTC DS1307
      Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00); // Початкова адреса регістру часу в DS1307

  // Запис даних у регістри DS1307
  Wire.write(decToBcd(second)); // Запис секунд (не використовується)
  Wire.write(decToBcd(minute)); // Запис хвилин
  Wire.write(decToBcd(hour)); // Запис годин
  Wire.write(decToBcd(day)); // Запис дня
  Wire.write(decToBcd(month)); // Запис місяця
  Wire.write(decToBcd(year)); // Запис року (останні дві цифри)

  Wire.endTransmission();
    }
  }

  // Інші операції
}





