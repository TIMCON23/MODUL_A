// функція передачі показників середовища 
// d serial, lcd1602, ESP8266
#pragma once
#include "main.h" // підключаємо головний файл з назвами функцій

void GET_data_sensors () {

  sensors_read();

  Serial.print(F("Temperature  struct: "));
  Serial.println(incubator_1.t1);
  
 
  incubator_1.h1=(float)si7021.measureHumidity(), 1;
  Serial.print(F("Humidity: ")); Serial.println(incubator_1.h1);
  // Serial.print (F("Температура округлена: " ));Serial.println (t);
  // Serial.print(F("Humidity:    ")); Serial.println(Incubatorincubator_1.h);
   
  incubator_1.tegg1= dsRead(0),2;
  incubator_1.tegg1=constrain(incubator_1.tegg1,1,60);
  Serial.print(F("Temperature egg: ")); Serial.println(incubator_1.tegg1);
  
 incubator_1.tw1= dsRead(1),2;
  Serial.print(F("Temperature water: ")); Serial.println(incubator_1.tw1);
  incubator_1.CO2=analogRead(SENSORGAZ_PIN);
  incubator_1.CO2 = constrain(incubator_1.CO2, 10, 3600);// рамки сенсора для уникнення фальшивого включення sensVal диапазоном от 10 до 150
   Serial.print(F("CO2: ")); Serial.println(incubator_1.CO2);
  delay(2000);

Serial.print(" t:"); Serial.print(si7021.getTemperatureFromPreviousHumidityMeasurement(), 1);
  Serial.print(" h:"); Serial.println(si7021.measureHumidity(), 1);




}


float dsRead (byte x)       { 

//    { 
  byte incubator_1 [2], addr[8][8],kol=0; 
  while  (ds.search (addr [kol]))  {   // пошук датчиків, визначення адреси та кiлькості датчиків
   for ( int i = 0;i < 8;i ++)  { 
  } 
  kol++;} 
 
  ds. reset_search () ;  // Скидання пошуку датчика 
  ds. reset () ;         // Ініціалізація, виконується скидання шини 
  ds. select (addr [x]) ; // Звернення до датчика за адресою 
  ds.write(0x3F);         // точность 0,5гр = 1F; 0,25гр = 3F; 0,125гр = 5F; 0,0625гр = 7F
  ds. write (0x44,0) ;  // Вимірювання температури з перенесенням даних в пам'ять 
  ds. reset () ;         // Ініціалізація, виконується скидання шини 
  ds. select (addr [x]) ; // Звернення до датчика за адресою 
  ds. write ( 0xBE ) ;     // Звернення пам'яті 
  incubator_1 [0] = ds. read () ; // Читання пам'яті byte low 
  incubator_1 [1] = ds. read () ; // Читання пам'яті byte high 
  float value = (( incubator_1 [1] << 8) | incubator_1 [0]) / 16.0 ;
 // int value = (( incubator_1 [1] << 8) | incubator_1 [0]) / 16.0 ;
  return  (float) value; // Розрахунок температури і висновок 

 // return  (int) value; // Розрахунок температури і висновок 
}   