         
         #pragma once
         #include "main.h" // підключаємо головний файл з назвами функцій
         
         void idetenficstion_moidel ()// функція присвоєння ідентифікатора модуля
         {         
              // if ((EEPROM.read(0))!=1) // якщо ячейка пам'яті 0 містить не "1" то це перше включення модуля  і запускаємо очищення всієї пам'яті
                // { 
        for (int i = 1; i < 257; i++) // записуємо у всі ячейки пам'яті 0
            { EEPROM.update(i, 0);}
                
                    //записуємо в пам'ять момент першого запуску модуля для генерації унікального номера
                    GET_DateTime();// читаємо годинник
                    EEPROM.update(200,bcdToDec(dateTime[1]));
                    EEPROM.update(202,bcdToDec(dateTime[2]));
                    EEPROM.update(204,bcdToDec(dateTime[4]));
                    EEPROM.update(206,bcdToDec(dateTime[5]));
                    EEPROM.update(208,bcdToDec(dateTime[6]));
                    
                    // пишемо в ячейки 55 щоб при перезагрузці не стерлись дані в пам'яті
                    
                   EEPROM.update(0,55); 
                   EEPROM.update(55,55);
                   EEPROM.update(255,55);
                                       
                    //виводимо серійний номер модуля
                       
                        int m=EEPROM.read(200); 
                        int H=EEPROM.read(202); 
                        int D=EEPROM.read(204); 
                        int M=EEPROM.read(206); 
                        int Y=EEPROM.read(208); 
                       
                        Serial.print(myText[1]);
                        Serial.print(Y);Serial.print(M);Serial.print(D);Serial.print(H);Serial.println(m);
                        Serial.println();
                        lcd.setCursor(0, 1);
                        lcd.print(myText[1]);
                        lcd.print(Y);lcd.print(M);lcd.print(D);lcd.print(H);lcd.print(m);
                        }         