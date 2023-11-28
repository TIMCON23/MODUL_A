// функція отримання дати і часу з модуля реального часу DS1307
//
#pragma once
#include "main.h"

void GET_DateTime()         {                    // отримуємо дані з годинника, дату і годину і хвилину
 
 Wire.beginTransmission(DS1307_ADDRESS);  // начинаем обмен с DS1307
 Wire.write(byte(0x00));          // записуємо адрес регістра, з якого стартують дані дати і часу
 Wire.endTransmission();          // завершуємо передачу
 int i = 0;                       // індекс даного елементу
 Wire.beginTransmission(DS1307_ADDRESS);  // функція обміну з DS1307
 Wire.requestFrom(DS1307_ADDRESS, 7);     // запит 7 байтів у DS1307

 while (Wire.available())         // цикл для передачі даних DS1307
  { dateTime[i] = Wire.read();    // читаем 1 байт и сохраняем в массив dateTime
    i += 1;
  }                       // инкрементуемo і додаємо індекс елемента масивуиндекс элемента массива
  
  Wire.endTransmission(); 
}
 