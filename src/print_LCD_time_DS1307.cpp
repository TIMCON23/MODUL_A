//  файл друку дати і часу в серіалі і на lcd1602
#include "main.h"
void print_Lcd_time()      {             //друкуємо на Lcd-екран дані з датчиків як  меню
  //minute=bcdToDec(dateTime[1]);
 // hour=bcdToDec(dateTime[2]);
  //dayOfMonth=bcdToDec(dateTime[4]);
  //month=bcdToDec(dateTime[5]);
  //year=bcdToDec(dateTime[6]);



lcd.setCursor(0, 0);           Serial.println();
if (dayOfMonth < 10)
  {lcd.print(F("0"));          Serial.print(F("0"));}
  lcd.print(dayOfMonth);       Serial.print(dayOfMonth);
  lcd.print(F("."));           Serial.print(F("."));
   
if (month < 10) 
  {lcd.print(F("0"));          Serial.print(F("0"));}
   lcd.print(month);           Serial.print(month);
  
  lcd.print(F("."));           Serial.print(F("."));
  lcd.print(year);             Serial.print(year);
  
  lcd.print(F("   "));          Serial.print(F("."));
 
if (hour < 10) 
  {lcd.print(F("0"));           Serial.print(F("0"));};
  lcd.print(hour);              Serial.print(hour);
  lcd.print(F(":"));            Serial.print(F(":"));

if (minute < 10) 
    { lcd.print(F("0"));        Serial.print(F("0"));}
  lcd.print(minute);            Serial.println(minute);

 
}