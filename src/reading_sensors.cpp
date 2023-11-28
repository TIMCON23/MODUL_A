
/*
 * Функція зчитування 
 * даних з сенсорів та портів
 */
#pragma once
#include "main.h" // підключаємо головний файл з назвами функцій
#include <DallasTemperature.h>

const float VOLTAGE_RESOLUTION = 5.0 / 1023.0;
const float VREF = 5.0;
const float RLOAD = 10.0;
const float RZERO = 76.63;
 
void sensors_read()         {
  
incubator_1.t1 = readSi7021Temperature(SI7021_ADDRESS);
incubator_1.h1 = readSi7021Humidity(SI7021_ADDRESS);


incubator_1.tegg1=getTemperatureBySensorName("tegg1");
//incubator_1.tegg1=dsRead(1),2; // зчитуємо температуру яйця
incubator_1.tegg1=constrain(incubator_1.tegg1,35,39); // обмежуємо температуру яйця


incubator_1.tw1=getTemperatureBySensorName("tw1");
//incubator_1.tw1=dsRead(0),2; // зчитуємо температуру води в ємності
incubator_1.tw1=constrain(incubator_1.tw1,5,70); // обмежуємо температуру яйця

incubator_1.t2=getTemperatureBySensorName("t2");
//incubator_1.tw1=dsRead(0),2; // зчитуємо температуру води в ємності
incubator_1.t2=constrain(incubator_1.t2,5,70); // обмежуємо температуру яйця



int sensorValue = analogRead(SENSORGAZ_PIN);
float ppm = convertToPPM(sensorValue);
 incubator_1.CO2 = round(ppm);
  
}


float getTemperatureBySensorName(const char* sensorName) {
  if (strcmp(sensorName, "tw1") == 0) {
    return incubator_1.tw1;
  } else if (strcmp(sensorName, "t2") == 0) {
    return incubator_1.t2;
  } else if (strcmp(sensorName, "tegg1") == 0) {
    return incubator_1.tegg1;
  } else {
    return 0.0; // Повернути значення за замовчуванням або обробити помилку
  } 
}

float readSi7021Humidity(byte x) {
  Wire.beginTransmission(x);
  Wire.write(0xE5); // Команда для зчитування вологості
  Wire.endTransmission();

  delay(50); // Почекайте протягом 50 мс для завершення зчитування

  Wire.requestFrom(x, 2);
  if (Wire.available() >= 2) {
    byte msb = Wire.read();
    byte lsb = Wire.read();
    unsigned int rawHumidity = (msb << 8) | lsb;

    // Формула для обчислення вологості
    float humidity = ((125.0 * rawHumidity) / 65536) - 6.0;

    return humidity;
  } else {
    // Помилка зчитування вологості
    return -999.99;
  }
}


float convertToPPM(int sensorValue) {
  float voltage = sensorValue * VOLTAGE_RESOLUTION;
  float resistance = (VREF * RLOAD) / (voltage * (1.0 - (voltage / VREF)));
  return 116.6020682 * pow((resistance / RZERO), -2.769034857);
}


float readSi7021Temperature(byte x)
 {
  Wire.beginTransmission(SI7021_ADDRESS);
  Wire.write(0xE3); // Команда для зчитування температури
  Wire.endTransmission();

  delay(50); // Почекайте протягом 50 мс для завершення зчитування

  Wire.requestFrom(SI7021_ADDRESS, 2);
  if (Wire.available() >= 2) {
    byte msb = Wire.read();
    byte lsb = Wire.read();
    unsigned int rawTemperature = (msb << 8) | lsb;

    // Формула для обчислення температури
    float temperature = ((175.72 * rawTemperature) / 65536) - 46.85;

    return (float) temperature;
  } else {
    // Помилка зчитування температури
    return -999.99;
  }
 }

/*float dsRead (byte x) 
 { 


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
*/