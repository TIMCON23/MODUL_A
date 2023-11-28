// контроль і перше внесення даних в годинник реального часу
// даніі отримані з wemosd1r2

#include"main.h"
#pragma once

const byte timeRequestCommand = 0x01; // Команда запиту часу

struct DateTime {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

DateTime receivedTime;

void Send_time_ESP () {/// Надіслати запит ESP8266 на отримання точного часу p отриманням дати і часу  і записом у структуру

sendTimeRequest();

  delay(1000); // Затримка між запитами
}

void sendTimeRequest() {
  Wire.beginTransmission(espAddress); // Адреса модуля ESP8266
  Wire.write(timeRequestCommand); // Відправка команди запиту часу
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("Команда успішно надіслана до модуля ESP8266");
  } else {
    Serial.println("Помилка при надсиланні команди до модуля ESP8266");
  }




}






void write_time_ds1307 () { //  запис часу в RTC ds1307

    Wire.beginTransmission(DS1307_ADDRESS);
   
   Wire.write(0x1);
   Wire.write(decToBcd(minute));
   Wire.write(0x2);
   Wire.write(decToBcd(hour)); 
   Wire.write(0x4);
   Wire.write(decToBcd(dayOfMonth));
   Wire.write(0x5);
   Wire.write(decToBcd(month));
   Wire.write(0x6);
   Wire.write(decToBcd(year));
   Wire.endTransmission();

}




  
  Wire.beginTransmission(espAddress);
  byte error = Wire.endTransmission();
  
  if(error==0)// якщо Мастер відправив ) - то 
  
  Wire.beginTransmission(espAddress);// шукаємо модуль ESP8266
  Wire.write(timeRequestCommand);
  Wire.endTransmission();

  delay(3000);  // Додано затримку для дочекання передачі даних

 if (Wire.available()) {
    byte deviceAddress = Wire.read();
    if (deviceAddress == espAddress) {
       
      DateTime receivedTime;
      Wire.readBytes((uint8_t*)&receivedTime, sizeof(receivedTime));
     
}

 }
 void sendRequestToMaster() {
  Wire.beginTransmission(masterAddress); // Адреса Мастера
  Wire.write(0x01); // Відправка даних (у цьому випадку - запит)
  Wire.endTransmission();
}