


// файл старту модуля подвійного контролю середовища
#pragma once
#include "main.h" // підключаємо головний файл з назвами функцій

// окремі функції


void setup() {
  Serial.begin(9600);
  Wire.begin(); // ds18b20
  //si7021.begin(); // si7021   
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);                  // вибираємо потужність радіосигналу
  radio.setDataRate( RF24_1MBPS );                 // вибираємо швидкість радіопередачі
  radio.enableAckPayload();                       //дозволяємо відправку даних у відповіді на вхідний пакет на входящий  
  radio.openWritingPipe(0x6868686868LL);          // відкриваємо трубу для зв'язку
 
  
  lcd.begin();                           // ініціалізуємо lcd екран
  lcd.backlight();                       // Підключаємо підсвітку екрана
  lcd.setCursor(0, 0); lcd.print(myText[0]);
  Serial.println(F("INCUBATOR TIM&Co...Start module...."));
  delay(5000); // даємо ESP8266  зловити інтернет
  
  
  // починаємо налагодження годинника реального часу
  
  // перевіряємочи чи є годинник на шині
  bool checkDS1307Presence()
   {
  Wire.beginTransmission(DS1307_ADDRESS);
  byte error = Wire.endTransmission();

      if (error == 0)// DS1307 знайдено на шині I2C
        {  GET_DateTime();// читаємо свій rtc ds1307 годинник
          print_Lcd_time();  // виводимо дату і час з rtc ds1307

            if(year<21)
             {flag_Clock=true;//якщо рік менше 21 то годинник не працює і піднімаємо флаг помилки
              Get_data_time_ESP8266(); // відправляємо запит на точний час і синхнронізацію часу з сервером точного часу
              write_time_ds1307 ();// записуєсо дані в годинник
              
       

      } 

         
     }
   
      else // DS1307 не знайдено на шині I2C
  {    
    lcd.setCursor(0, 1); 
    lcd.print(warningMessage[1]);
    delay(500);
    lcd.print(warningMessage[15]);

    Serial.print(warningMessage[1]);
    Serial.println(warningMessage[15]);
  
  
  }
    
   }
  
  
  //перевіряємо чи модулю ідентифікований в системі TIMCON 
  // читаємо з ячейки 
  int a = EEPROM.read(0);
  int b = EEPROM.read(55);
  int c = EEPROM.read(255);
  
  int chacksumm = a+b-c;
  
  if ((!flag_Clock)&&(!chacksumm==55)) // якщо флаг rtc ds1307 не піднятий включення піднято
    idetenficstion_moidel(); //перевірка першого включення і присвоєння власного коду IDE


    
         
  delay(4000);
 // пишемо в память lcd символи
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
  radio.setChannel(115);                          //вибираємо канал для радіозв'язку (від 0 до 127)
  
  
  for (byte i = 4; i < 9; i++)
  {pinMode(i, OUTPUT);
  };           // усі піни з D4 по D8 робимо виходами
//  pinMode(extendPin, OUTPUT); // порт для висунення штоку актуатора
 // pinMode(retractPin, OUTPUT);// порт для засування штоку актуатора
    
  myPID.SetOutputLimits(10, WindowSize);
  myPID.SetMode(AUTOMATIC);
  if (EEPROM.read(10) == 255 && EEPROM.read(4) == 255){
        EEPROM.write(10, 10);
        EEPROM.write(11, 0);
        EEPROM.write(12, 240);
        EEPROM.write(13, 65);
   }
   EEPROM.get(10, Setpoint);
   delay(200);
  
  
  
  // перевіряємо справність сенсорів і систем

  // датчие температури і вологості Si7021
  bool checkSi7021Presence() {
  Wire.beginTransmission(SI7021_ADDRESS);
  byte error = Wire.endTransmission();

  if (error == 0) {
    // Si7021 знайдено на шині I2C
    flag_sensor_Si7021= false;
  } else {
    // Si7021 не знайдено на шині I2C
    flag_sensor_Si7021= true;
     }
}
  
  // перевірка сенсорів DF18b230

  void checkDS18B20Presence() {
  OneWire oneWire(ds);
  //byte address[8];

// Масив адрес датчиків
byte addresses[MAX_SENSORS][8];
  int sensorCount = 0;

  // Перебираємо всі пристрої на шині OneWire
  while (oneWire.search(address)) {
    // Перевірка, чи це DS18B20
    if (address[0] == 0x28) {
      //Serial.print("DS18B20 знайдено. Унікальний номер: ");
      //printAddress(address);
      //Serial.println();

      // Присвоюємо унікальний номер сенсора полю в структурі incubator_1
      if (sensorCount == 0) {
        assignSensorNumber(address, incubator_1.tw1);
      } else if (sensorCount == 1) {
        assignSensorNumber(address, incubator_1.t2);
      } else if (sensorCount == 2) {
        assignSensorNumber(address, incubator_1.tegg1);
      }

      sensorCount++;
    }
  }

  if (sensorCount == 0) {
    Serial.println("Сенсори DS18B20 не знайдені.");
    flag_sensor_eggs = true;
    flag_sensorWatterBox = true;
    flag_sensor_duble_t2 = true;
  } else {
    Serial.print("Загальна кількість сенсорів DS18B20: ");
    Serial.println(sensorCount);
  }

  oneWire.reset_search();
}

void printAddress(byte* address) {
  for (int i = 0; i < 8; i++) {
    if (address[i] < 16) {
      Serial.print("0");
    }
    Serial.print(address[i], HEX);

    if (i < 7) {
      Serial.print(":");
    }
  }
}

void assignSensorNumber(byte* address, float& sensor) {
  uint32_t uniqueNumber = 0;
  for (int i = 0; i < 4; i++) {
    uniqueNumber |= ((uint32_t)address[4 + i]) << (i * 8);
  }
  sensor = uniqueNumber;
}

  
  

// перевірка сенсорів MQ135

  bool checkMQ135Sensor() {
  pinMode(SENSORGAZ_PIN, INPUT);
  int sensorValue = analogRead(SENSORGAZ_PIN);
  return (sensorValue >= 0 && sensorValue <= 1023);
}
  
  
  
  
  
  
  
  
  
  
   Serial.println(F("INCUBATOR TIM&Co...Start module."));
  ton();
  
   Mane_menu(); // задаємо функцію для екрана доки не буде нажата кнопка з меню
delay(1000);

}






void loop(){
  // холостий цикл
if(flag_Startincubation)
  {Mane_menu();
  mainMenuDraw();
  drawCursor();
  operateMainMenu();
  }
  else {

    // виконуємо холостий код

 // -модуль періодично перевіряє присутність сенсорів, їх роботоздатність, наявність робочого стану каналів зв'язку та стан релейних модулів;
 // -отримує точний час від супутнього модуляWEMOSd1R2 (при неможливості отримання зчитує дату і час з RTC ds1307)
 // -періодично зчитує дані з сенсорів та виводить їх LCD1602 та транслює в serial)
 // - перевіряє канали зв'язку на придмет наявності команд,  а при їх наявності - їх виконує
  GET_DateTime();
  //виводимо дані в серіал(щоб бачити по блютузу) і на LCD
  send_Lcd_Clock();
  
  sensors_read();
  Serial.print(F("Temperature  incubator: ")); Serial.println(incubator_1.t1);
lcd.clear();
lcd.setCursor (0,0);
lcd.print(myText[33]);lcd.print(incubator_1.t1);lcd.print(myText[19]); //виводимо температуру

Serial.print(F("Humidity  incubator: ")); Serial.println(incubator_1.h1);
lcd.setCursor (0,1);
lcd.print(myText[15]);lcd.print(incubator_1.h1);lcd.print(myText[14]); //виводимо температуру
  
  }

  



/*
  
  if (incubator_1.dey1<=21) {

// запускаємо перевірку часу до включення перевороту
if (millis()- timer_interval_incubator>=PERIOD3)
{
control_perevorot(); // функція перевороту лотків
             do {
       timer_interval_incubator += PERIOD3;
      if (timer_interval_incubator < PERIOD3) break;  // переповнення типу uint32_t
     } while (timer_interval_incubator < millis() - PERIOD3); // захист від пропуску крока
      }


*/
   // контролюємо параметр температури PID
 if (millis() - windowStartTime > WindowSize)
  {  Input=(float)si7021.getTemperatureFromPreviousHumidityMeasurement(),1;
  Serial.print(F("Input: "));Serial.println(Input);
  myPID.Compute();
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime)
  {digitalWrite(RELAY2_PIN, HIGH);
   
  }
  else {digitalWrite(RELAY2_PIN, LOW);}
 //}
 
 
 
 // відправляємо дані по радіоканалу
  if  (millis() - timer1 >= PERIOD1)          // кожних 5 хв відправляємо дані по радіо і по I2C
     {
       if (!radio.isPVariant())
          {flag_Radio=true;
         }
        else { // якщо радіо працює то шлемо
      sensors_read(); // Отримуємо дані для передачі (наприклад, з датчиків або інших джерел)
    if(radio.write(&incubator_1, sizeof(incubator_1))); //відправляємо пакет структури даних
  Serial.println("Структура даних відправлена по радіоканалу");
 if (radio.isAckPayloadAvailable()) {             // чекаємо відповіді в пакеті...
  radio.read(&NRF_message,sizeof(NRF_message));   //... и имеем переменную message с числом ...0-256 от приемника.
  delay(75);
  Serial.print(myText[3]); Serial.println(NRF_message);
    }
      send_incubator_1I2C(); // відправляємо дані по шині на супутній модульESP8266
             do {
       timer1 += PERIOD1;
      if (timer1 < PERIOD1) break;  // переполнение uint32_t
     } while (timer1 < millis() - PERIOD1); // защита от пропуска шага
      }
     }
if (Serial.available() > 0) // перевіряємо чи є команди передані по bluetooth
        {
    String bufString = Serial.readString();             // читаємо з порту як рядок символів
    byte dividerIndex = bufString.indexOf(';');           // шукаємо індекс кінця команди
    String buf = bufString.substring(0, dividerIndex);    // створюємо рядок чисел, від першого числадо індексу кінця комани строку с первым числом
    delay(10);
    bluetoothCommand=buf.toInt();                         // перетворюємо  (String  y int) команду в цифровукоманду
    delay(100);
    Serial.print(myText[50]); Serial.println(bluetoothCommand) ; // виводимо команду, для відладки 
    read_bluetoothComand();// запускаємо функцію читання блютуз команди
   }

}









void send_incubator_1I2C()         {                    //передаємо і отримуємо дані по шині І2С
 
Wire.beginTransmission (espAddress); // відправляємо дані по шині І2С
 int t =incubator_1.t1*100;
Serial.print (F("Температура округлена: " ));
Serial.println (t);

Wire.write(t>>8);
Wire.write(t&0xff);

int h = incubator_1.h1*100;
Wire.write(h>>8);
Wire.write(h&0xff);
 
int tegg = incubator_1.tegg1*100;
Wire.write(tegg>>8);
Wire.write(tegg&0xff);

int tw1 = incubator_1.tw1*100; 
Wire.write(tw1>>8);
Wire.write(tw1&0xff);


Wire.write(incubator_1.CO2>>8);
Wire.write(incubator_1.CO2&0xff);

Wire.write(incubator_1.routing1>>8);
Wire.write(incubator_1.routing1&0xff);
 
Wire.write(incubator_1.dey1>>8);
Wire.write(incubator_1.dey1&0xff);

Wire.write(incubator_1.number1>>8);
Wire.write(incubator_1.number1&0xff);

//Wire.write(incubator_1.v1);
//Wire.write(incubator_1.r12);
//Wire.write(incubator_1.r22);
//Wire.write(incubator_1.r32);
//Wire.write(incubator_1.r42);
//Wire.write(incubator_1.r52);
//Wire.write(incubator_1.r62);
//Wire.write(incubator_1.radio);
//Wire.write(incubator_1.Si7021);
//Wire.write(incubator_1.DS18b20);
//Wire.write(incubator_1.RTC_ds1307);
Wire.endTransmission ();         // завершуємо передачу даних на модуль зв'язку

   delay(500);
  //чекаємо зворотніх даних
   int i=0;
   int I2C_messageLast=0;
   Wire.requestFrom(SLAVE_ADDRESS, 2);     // запросить 10 байтов от ведомого устройства #2
  Serial.println(F("Sent message I2C; "));
  while(Wire.available())     // ведомое устройство может послать меньше, чем запрошено
  { byte c = Wire.read();     // принять байт как символ
    //Serial.print(c);          // напечатать символ
 if (i==0)
 I2C_messageLast = ((c & 0xff) << 8); else I2C_messageLast = I2C_messageLast | c;
    i++;
    }
    if((I2C_messageLast>=101)&&(I2C_messageLast<=199))
  I2C_message=I2C_messageLast-100;
    Serial.println(I2C_message);


    Wire.beginTransmission (SLAVE_ADDRESS);
    Wire.write(1);
    Wire.endTransmission ();         // завершуємо передачу даних на модуль зв'язку
  }                               //функція отримання температури з шини sd18b20





/*void sent_Radio_incubator_1()      {
    
  radio.powerUp();
  delay(75);
  if (!radio.isPVariant()){flag_Radio==true; }
   else {flag_Radio==false;}
   if(radio.write(&incubator_1, sizeof(incubator_1)))
 {
 if (radio.isAckPayloadAvailable()) {             // чекаємо відповіді в пакеті...
  radio.read(&NRF_message,sizeof(NRF_message));   //... и имеем переменную message с числом 111 от приемника.
  delay(75);
  Serial.print(myText[15]); Serial.println(NRF_message);
  
  radio.powerDown();
  
  }
  }
else
{ Serial.println(myText[16]);}
  
  }
  */
void read_routine_feeding() {
   switch (incubator_1.routing1){
  case 1: //  режим утримання бройлера
          // lcd.print(myText[33]);
        Serial.println(myText[33]);
    break;
  case 2:// параметри утримання індиків
         //lcd.print(myText[34]); 
         Serial.println(myText[34]);
    break;
  case 3:// параметри утримання качок
         //lcd.print(myText[35]);
         Serial.println(myText[35]);
    break;
  case 4:// параметри утримання перепелів
         //lcd.print(myText[36]);
        Serial.println(myText[36]);
    break;
 case 5:// параметри утримання фазанів
        //lcd.print(myText[37]);
        Serial.println(myText[37]);
    break;
 case 6:// параметри утримання цесарки
        //lcd.print(myText[38]);
        Serial.println(myText[38]);
    break;
 case 7:// параметри утримання 
        //lcd.print(myText[39]);
        Serial.println(myText[39]);
    break;
 case 8:// параметри утримання 
        //lcd.print(myText[40]);
        Serial.println(myText[40]);
    break;
 case 9:// параметри утримання 
        //lcd.print(myText[41]);
        Serial.println(myText[41]);
    break;
   }
}
void send_LCD_sensors()     { 
  lcd.setCursor(0, 1);
  lcd.print(myText[51]);
   lcd.setCursor(0, 1);
  lcd.print(myText[3]);     // для температури
  lcd.print(incubator_1.t1);          // пишемо значення температури
  lcd.print((char)223);lcd.print(myText[32]);
  delay(1500);              // затримка 3 сек для читання


  lcd.setCursor(0, 1);  // курсор на початок другого рядка
  lcd.print(myText[27]);     // для вологості
  lcd.print(incubator_1.h1);
  lcd.print(myText[26]);// пишемо значення вологості
  delay(1500);              // затримка 3 сек для читання

  // виводимо дані загазованості. Окремий цифровий канал при перевищенні норми загазованості включає звукову сигналізацію
  lcd.setCursor(0, 1); // курсор на другий символ 1 рядка (пишемо 1, 0)
  lcd.print(F("GAZ: ")); 
   lcd.print(incubator_1.CO2);
 // lcd.print(F(" ppm       "));
  delay(1500);              
  
  lcd.clear();
  lcd.setCursor(0, 1);
   // виводимо температури води в баці
  lcd.setCursor(0, 0);
    if(incubator_1.tw1==-127) {lcd.print(myText[5]);}
 else
  {lcd.print(myText[45]);
  lcd.print(incubator_1.tw1);lcd.print((char)223);lcd.print(myText[32]);}
   // виводимо температур модуля
   
    
    lcd.setCursor(0, 1);
    if(t_module==-127)
  {lcd.print(myText[4]);}
 else
  {lcd.print(myText[46]);
  lcd.print(incubator_1.tw1);lcd.print((char)223);lcd.print(myText[32]);}
   
   delay(1500);
 lcd.setCursor(0, 0);
    
  lcd.print(myText[47]);
  lcd.setCursor(0, 1);
  lcd.print(sensor1);lcd.print((char)223);
  lcd.print(sensor2);lcd.print((char)223);
  lcd.print(sensor3);lcd.print((char)223);
 
   delay(1500);
  
//Serial.print(F("Birds: "));

 lcd.clear();
 lcd.setCursor(0, 0);
 read_routine_feeding();
 lcd.print(F(" Day:")); lcd.print(incubator_1.dey1);
 lcd.setCursor(0, 1);
 lcd.print(F("Num:")); lcd.print(incubator_1.number1);
 lcd.print(F(" End:")); lcd.print(all_feeding-incubator_1.dey1);
  
 Serial.print(F("Num: ")); Serial.print(incubator_1.number1);
 Serial.print(F("; Day: ")); Serial.print(incubator_1.dey1);
 Serial.print(F("; End: ")); Serial.println(all_feeding-incubator_1.dey1);
 Serial.print(myText[3]);Serial.print(incubator_1.t1);Serial.println(myText[32]);
 Serial.print(myText[27]);Serial.print(incubator_1.h1);Serial.println(myText[26]);
 Serial.print(myText[45]);Serial.print(incubator_1.tw1);Serial.println(myText[32]);
 Serial.print(myText[46]);Serial.print(t_module);Serial.println(myText[32]);
 Serial.print(F("GAZ: ")); Serial.println(incubator_1.CO2); //Serial.println (F(" ppm;"));
     
 }
