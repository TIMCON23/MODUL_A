
// файл оголошення всіх бібліотек і назв функцій 
#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include "Arduino.h"
//#include <Si7021.h>
//Si7021 si7021;
#include <PID_v1.h>
double Setpoint, Input, Output;
double Kp=2, Ki=5, Kd=1.5;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
#define TEMP_MAX 38.6                        // Граничні температури для інкубатора
#define TEMP_MIN 36.5
int WindowSize = 5000;

const int MAX_SENSORS = 3;

//unsigned long previousMillis = 0;  // Зберігає час останнього включення актуатора
//unsigned long timer_work_ictuator = 2UL * 60UL * 1000UL;  // Інтервал увімкнення актуатора (2 хвилини)- змінна для виставлення часу роботи(у мікросекундах) за замовчуванням  актуатора для автоматизації перевороту яєць//
//unsigned long timer_interval_incubator = 90UL * 60UL * 1000UL,  // Інтервал вимкнення актуатора (90 хвилин)змінна для виставлення періоду між переворотом яєць з одного положення в інше (у мікросекундах) за замовчуванням актуатора для автоматизації перевороту яєць//

int windowStartTime;

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9, 10);                   // створюємо об'єкт з назваю-( "radio") NRF24L01 і порти підключення CE(9) і SCN(10) радіомодуля, крім того підключаємо SCK до 13, MO/MOSI до 11, MI/MISO до 12,
const uint64_t pipe2=0x6868686868LL;


const int espAddress = 9; // Адрес ESP8266 на шині I2C
const int DS1307_ADDRESS = 0x68; // Адреса DS1307 на шині I2C
const int SI7021_ADDRESS = 0x40; // Адреса Si7021 на шині I2C

byte bcdToDec(byte val){ return ( (val/16*10) + (val%16) );}//переводимо в нормальне число
byte decToBcd(byte val){return ( (val/10*16) + (val%10) );}// переводимо в двоїчно-десяткове


byte minute, hour, dayOfMonth, month, year;
byte dateTime[7];      // 7 байт для зберігання дати і часу з модуля
int readKey, clockPos, menuPage,activeButton, button,cursorPosition,sensor1,sensor2,sensor3,q,lastYear,bluetoothCommand, NRF_message=0,I2C_message=0,
   Hmin,Hmax,twmax,twmin,gazmax,all_feeding, correctDey;
String menuItems[] = {"Clock", "Start module", "Parametrs", "Device Timers",};
                       // налаштування годинника, встановлення таймеру нагадування, встановлення параметрів контролю, 
                       //встановлення таймерів роботи додаткового обладнання, "переведення сенсорів їх коректування)
int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);  //Переменная для кнопок навигации
#include <OneWire.h>                // бібліотека для роботи з протоколом OneWire 
OneWire ds(14);                     // порт (А0=D14) сенсорів DS18b20
#define PERIOD1 63000               // 1000*60*2період для виконання функції виведення даних на LCD 1602 і в Serial
#define PERIOD2 123000
#define PERIOD3 123000
uint32_t timer1 = 0;              // таймер для перевірки радіовідправлень
uint32_t timer2 = 0; 
#include <LiquidCrystal_I2C.h>        // бібліотека по роботі з lcd дисплеєм на шині 12С
LiquidCrystal_I2C lcd(0x27,16,2);     // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой 

#define tonePin 2                   // підключення звукового сповіщувача (бузера)
#define SENSOR220V_PIN 3            // порт D2 - порт переривання наявність 220 вольт
#define RELAY1_PIN 4                // порт D4  r1 - вентилятор для нагнітання вологості через ванночку
#define RELAY2_PIN 5                //ШИМ// порт D5  r2 - шим опалення: тепловентилятор, калорифер або нагрів повітря карбоновий шнур
#define RELAY3_PIN 6                //ШИМ// порт D6  r3 - шим циркуляція повітря: вентилятор для перемішування повітря (циркуляція)    
#define RELAY4_PIN 7                // порт D7  r4 - додаткове опалення: тен або лампи накалювання(в т.ч. як страховка) розігріву інкубатора
#define RELAY5_PIN 8                // порт D8  r5 -  витяжка - вентилятори швидкого провітрювання-охолодження


//А0- (D 14) -  шина сенсорів DS18b20 (температура яйця, температура води в ванні) 
#define extendPin 15  // Пін для мотора лотка перевороту//А1- (D 15) (переворот яєць через) в коді добавити секудни для закінсення руху по досягненню крайнього положення
#define retractPin 16  // Пін для активації штоку актуатора//А2- (D 16) -  вихід на актуатор вниз (переворот яєць через тележку)в коді добавити секудни для закінсення руху по досягненню крайнього положення

#define Water_level 17              // порт A3- D17 - рівень води в зволожувачі          
//А4- (D 18) -  шина І2С SDA
//А5- (D 19) - шина І2С SCL
#define Button_menu_PIN A6          // A6       - кнопка для меню
#define SENSORGAZ_PIN A7            // A7       - давач газу CO2   



volatile boolean flag_power,flag_Watter_Box,//флаги роботи електрики,  наявності води у зволожувачі
  flag_FirstIndetefication, // флаг першого включення і присвоєння універсальног номера
  flag_Startincubation,// флаг запуску інкубації
  flag_Clock,//флаги стану годинника DS1307,
  flag_Radio, //  та nrf24L01 - якщо true то не працюють або не відповідають
  flag_sensor_Si7021, // флаг наявності і справності сенсора Si7021
  flag_sensor_eggs,// флаг наявності і справності сенсора DS18b20 на яйці
  flag_sensor_duble_t2, // флаг страховочного сенсора температури повітря в інкубаторі
  flag_sensorWatterBox,// флаг наявності і справності сенсора DS18b20 в ванні нагнітання вологості
  flag_sensor_module, // флаг наявності і справності сенсора DS18b20 на модулі реального часу DS1307 
  flag_RELAY1, flag_RELAY2,flag_RELAY3,flag_RELAY4,flag_RELAY5,flag_RELAY6; //флаги релейних модулів
 
 int t_module;     // температура модуля аналоговий сенсор на платі мк для уникнення перегріву плати
 

const char* warningMessage[]   =  {// масив тривожних повідомлень, номер і кількість байт
  "RadioNRF24L01 OFF",         //  0       20
  "ClockRTC1307 OFF",         //   1       30
  "Sensor Si7021 OFF! ",      //   2       30 
  "Sensor eggs OFF! ",        //   3       30
  "Sensor modul OFF",         //   4       32
  "Sensor waterTenck OFF",    //   5       30
  "NO water in Tank",         //   6       32
  "Sensor СО2 OFF",           //   7       30
  "Warning! Door open! ",     //   8       30
  "Warning! Temp critical!",  //   9       30
  "Warning! Temp egg critical!", //10      30
  "Warning! Hum critical!",   //   11       30
  "Warning! CO2 critical!",   //   12       30
  "Warning! 220! OFF!",       //   13       30
  "Warning! tmodule critical!" // 14       20
  "Change battery"            //  15       15  
};

const char* myText[]   =  {               // масив технічних даних і відладки
  "timCon.UA.2023 ",         //   0   //унікальний номер девайса,
      "IDE:" ,                //   1
  "I2C sent: ",               //   10 - 2
  "Radiomes sent:",           //   15 - 3
  "Radiomes no sent",         //   16 - 4
  "Control devaises:",        //   17 - 5
  "TIMER dey open. ",         //   18 - 6
  "TIMER dey closed." ,       //   19 - 7
  "Routine incubation: ",      //  20 - 8
  "Incubating dey: ",          //  21 - 9
  "END for deys :" ,          //   22 - 10
  "Number eggs: ",            //   23 - 11
  "All dey incubation: ",     //   24 - 12
  "Current settings: ",       //   25 - 13
  "%HR;",                     //   26 - 14
  "H incubator: " ,           //   27 - 15
  "END settings ..../",       //   29 - 16
  "SAVE settings...." ,       //   30 - 17
  "Start timer deys!" ,       //   31 - 18
 "C;",                        //   32 - 19 
"Brooler, ",                  //   33 - 20
"Tyrken, ",                   //   34 - 21
"Duck, ",                     //   35 - 22
"Quail, ",                    //   36 - 23
"Pheasan, ",                  //   37 - 24
"Numida, ",                   //   38 - 25
"Anser,  ",                   //   39 - 26
"Strays, ",                   //   40 - 27
"Manual ",                    //   41 - 28
"Restart module...",          //   42 - 29
"Тривожне повідомлення відправлено"// 43- 30
"t water: ",                  //   45 - 31
"t module: ",                 //   46 - 32
"T incubator: ",              //   47 - 33
"RadioNRF24L01 OK!:",         //   48 - 34
"ClockRTC1307 OK!:",          //   49 - 35
"bluetoothCommand:",          //   50 - 36
"                ",           //   51 - 37
"\1",                         //   52 - 38
"   Thank you!,   ",          //   53 - 39
"T_Input:",                    //   54 - 40
"T_Setpoint:",                 //   55 - 41
"Hmax:",                      //   56 - 42
"Hmin:",                      //   57 - 43
"twmax",                      //   58 - 44
"СO2max",                      //  59 - 45
"t eggs:" ,                     //  60 - 46
"t sensor module" ,              //  61 - 47
" ppm",                         // 62-48
" CO2",                          // 63-49
"twmin",                        //50
"Kp-",                           //51
"Kі-",                            //52
"Kd-",                             //53

};
struct data  {  //26 байти           //структура для передачі даних з інкубатора на центропульт
  int routing1;      // 2,режим утримання-вид птиці
  int number1;       // 2,к-сть яєць штук
  int dey1;          // 2,к-сть днів інкубації
  float t1;          // 4 , температура в інкубаторі Si7021
  int h1;            //2,  вологість в інкубаторі Si7021
  float tegg1;       // 4,температура яйця ds18b20
  int CO2;          // 2,рівеньCO2 в інкубаторі MQ135
  float tw1;        // 4,температура води в ємності для зволоження
  float t2;         // 4 температура в інкубаторі сенсор DS18b20 страховочний для контролю температури в ынкубаторі

  };
data incubator_1; // дані інкубатора
 //char*ReleStage []=
 // byte water_incubator_1;           // 1,наявність води в баці з водою - 
  //byte 220_Volt_incubator_1;           //1,стан мережі 220 Вольт
  //byte main_fane_incubator_1;        //1,стан реле основного вентилятора-перемішувача курника
  //byte main_heat_incubator_1;        // 1,стан реле основного обігріву 
  //byte r3_incubator_1;        // 1,стан реле додаткового обігріву
 // byte r4_incubator_1;        // 1,стан реле вентилятори для нагнітання вологості
  //byte r5_incubator_1;        // 1,стан реле перевороту яць 
  //byte r6_incubator_1;        // 1,стан реле витяжної вентиляції охолодження
  //byte radio_incubator_1;     // 1,стан роботи  радіопередавача
  //byte Si7021_incubator_1;    // 1,стан роботи сенсора вологості і температури
 // byte DS18b20;   // стан роботи  шини датчиків
 // byte RTC_ds1307;   // стан роботи  годинника реального часу
byte downArrow[8] =  { //стрілка вниз
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b10101, // * * *
  0b01110, //  ***
  0b00100  //   *
};
byte upArrow[8] =    { //стрілка вверх
  0b00100, //   *
  0b01110, //  ***
  0b10101, // * * *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100, //   *
  0b00100  //   *
};
byte menuCursor[8] = { //стрілка напрямку вправо 

  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

// назви функцій


void Get_data_time_ESP8266();//запит на точний час в ESP8266
void print_Lcd_time();// lcd1602
void GET_data_sensors ();// відправка параметрів в serial, esp8266, lcd1602
void checkDS18B20Presence();
void write_time_ds1307 ();
void Mane_menu();
void mainMenuDraw();
void drawCursor();
void operateMainMenu();
void idetenficstion_moidel (); // функція встановлення індивідуального номера девайса при першому включення
void send_radio();// відправка тривожних повідомлень
void ton();// озвучення команд
void GET_DateTime(); // читаємо внутрішній годинник DS1307
void sensors_read(); //  читаємо температуру з шини датчиків DS18b20: яйце, вода, модуль
void send_Lcd_Clock(); // виводимо дані з годинника реального часу на LCD1602
void send_LCD_sensors(); // виводимо дані з сенсорів на на LCD1602
void parameter_control(); // перевірка дотримання встановлених параметрів
void send_dataI2C();// відправка пакету даних по шині I2C в модуль супутник
void reading_command(); // читання отриманих команд через bluetooth
    
        