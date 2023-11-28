#pragma once
#include"main.h"



void reading_command() {
  // установка режимів інкубації вибір птахів)
  if (((bluetoothCommand>= 1)&&(bluetoothCommand<=9))||((NRF_message>=1)&&(NRF_message<=9)))
      {incubator_1.routing1=(bluetoothCommand+NRF_message);// в структуру записуємо номер режиму інкубації
      EEPROM.put(201,incubator_1.routing1);
      delay(10);
      Serial.print(myText[20]);
      read_routine_feeding();
      }
  if ((bluetoothCommand == 11)||(NRF_message == 11)||(I2C_message==11))// якщо прийшла команда - 11 та реле не активоване то його включаємо 
      { if (digitalRead(RELAY1_PIN)==LOW)
      {digitalWrite(RELAY1_PIN, HIGH );// включаємо вентилятор для нагнітання вологості
      Serial.println(F("ON humidity-fan.")); 
      flag_RELAY1 == true;
      }
       else
      {digitalWrite(RELAY1_PIN, LOW);
      Serial.println(F("OFF humidity-fan."));
      flag_RELAY1 == false;}
     }

if ((bluetoothCommand == 12)||(NRF_message == 12)||(I2C_message==12))// якщо прийшла команда - 12 та реле не активоване то його включаємо реле 
      { if (digitalRead(RELAY2_PIN)==LOW)
      {digitalWrite(RELAY2_PIN, HIGH );// включаємо головний нагрівальний кабель інкубатора
      Serial.println(F("ON top-heating.")); 
      flag_RELAY2 == true;
      }
       else
      {digitalWrite(RELAY2_PIN, LOW);
      Serial.println(F("OFF top-heating."));//виключаємо головний нагрівальний кабель інкубатора
      flag_RELAY2 == false;}
     }

if ((bluetoothCommand == 13)||(NRF_message == 13)||(I2C_message==13))// якщо прийшла команда - 13 та реле не активоване то його включаємо 
      { if (digitalRead(RELAY3_PIN)==LOW)
      {digitalWrite(RELAY3_PIN, HIGH );// включаємо головний вентилятор перемішування повітря
      Serial.println(F("ON top-fan.")); 
      flag_RELAY3 == true;
      }
       else
      {digitalWrite(RELAY3_PIN, LOW);//виключаємо головний вентилятор перемішування повітря
      Serial.println(F("OFF top-fan."));
      flag_RELAY3 == false;}
     }
if ((bluetoothCommand == 14)||(NRF_message == 14)||(I2C_message==14))// якщо прийшла команда - 15 та реле не активоване то його включаємо 
      { if (digitalRead(RELAY4_PIN)==LOW)
      {digitalWrite(RELAY4_PIN, HIGH );// включаємо додатковий нагрів для пришвидшення нагріву
      Serial.println(F("ON second-heating.")); 
      flag_RELAY4 == true;
      }
       else
      {digitalWrite(RELAY4_PIN, LOW);// виключаємо додатковий нагрів для пришвидшення нагріву
      Serial.println(F("OFF second-heating."));
      flag_RELAY4 == false;}
     }

// команди для актуатора
/*if ((bluetoothCommand == 15)||(NRF_message == 15)||(I2C_message==15))// якщо прийшла команда - 15 та реле не активоване то його включаємо 
      { if (digitalRead(RELAY5_PIN)==LOW)
      {digitalWrite(RELAY5_PIN, HIGH );// включаємо вентилятор провітрювання (охолодження)
      Serial.println(F("ON air-fan.")); 
      flag_RELAY5 == true;
      }
       else
      {digitalWrite(RELAY5_PIN, LOW);// виключаємо вентилятор провітрювання (охолодження)
      Serial.println(F("OFF air-fan."));
      flag_RELAY5 == false;}
     }

if ((bluetoothCommand == 16)||(NRF_message == 16)||(I2C_message==16))// якщо прийшла команда - 16 та реле не активоване то його включаємо 
      { if (digitalRead(RELAY6_PIN)==LOW)
      {digitalWrite(RELAY6_PIN, HIGH );// включаємо переворот (подаємо напругу на актуатор перевороту)
      Serial.println(F("ON actuator.")); 
      flag_RELAY6 == true;
      }
       else
      {digitalWrite(RELAY6_PIN, LOW);// виключаємо переворот (неподаємо напругу на актуатор перевороту)
      Serial.println(F("OFF actuator."));
      flag_RELAY6 == false;}
     }
*/
if (((bluetoothCommand>=10001)&&(bluetoothCommand<=10999))||((NRF_message>=10001)&&(NRF_message<=10999))) // команда записує в пам'ять к-сть днів утримання (від 1 до 999 днів)
    {all_feeding = ((bluetoothCommand+NRF_message)-10000); // к-сть днів усього - максимумально 999 днів(30999)
      EEPROM.put(280,all_feeding);
     Serial.print(myText[24]); Serial.println (all_feeding); 
 }
//__________________________технічні команди контролю за роботою модуля______________
  if ((bluetoothCommand== 200)||(NRF_message== 200)||(I2C_message==200))
    { Serial.println(myText[42]);
     //delay(500);
    asm volatile("jmp 0x00");                         // функція перезагрузки ардуино   
     }
  if ((bluetoothCommand==70)||(NRF_message==70))// виводимо стан усіх модулів  і стан сенсорів
      {  if(flag_Radio)Serial.println (myText[0]);
          else {Serial.println (myText[48]);}
        // send_Lcd_Clock();//}
      
        
        if(flag_sensor_Si7021)Serial.print (myText[2]);
          else {Serial.print(myText[47]);Serial.print(incubator_1.t1);Serial.println(myText[32]);
                Serial.print(myText[27]);Serial.print(incubator_1.h1);Serial.println(myText[26]);}
       
      //  if(flag_sensor_module)Serial.print (myText[4]);
      //    else {Serial.print(myText[61]);Serial.print(incubator_1.tmodule1);Serial.println(myText[32]);}
        
         
         
        
        if(flag_sensorWatterBox)Serial.print (myText[5]);
         else
         { Serial.print(myText[45]);Serial.print(incubator_1.tw1);Serial.println (myText[32]);}
       
        
        if(flag_sensor_eggs)Serial.print (myText[3]);
                  else   { Serial.print(myText[60]); Serial.println(incubator_1.tegg1);Serial.print (myText[32]);}
            
        
      }
  if ((bluetoothCommand==76)||(NRF_message==76))// виводимо дані усіх станів портів
        { // замінити на тернарний 

              Serial.println (F("obihriv1: - "));// ГОЛОВНЕ РЕЛЕ НАГРІВУ
              Serial.println ((digitalRead(RELAY1_PIN)==1)? "ON" : "OFF");// твердотільне?
         
          if ((digitalRead(RELAY2_PIN)==1))Serial.println (F("OPEN light."));
          if ((digitalRead(RELAY3_PIN)==1))Serial.println (F("OPEN Fan-exit."));
          if ((digitalRead(RELAY4_PIN)==0))Serial.println (F("OPEN water pump"));
      
        }
      
         if ((bluetoothCommand==77)||(NRF_message==77))// виводимо встановлені параметри
      {  
      Serial.print(myText[41]); Serial.print (Setpoint); Serial.println(myText[19]);//55// 54
   
      Serial.print(myText[56]); Serial.print (Hmax); Serial.println(myText[14]);//55//"Hmax:", //56
      Serial.print(myText[57]); Serial.print (Hmin); Serial.println(myText[14]);//55//"Hmin:",// 57
     
     Serial.print(myText[58]); Serial.println  (twmax);//"twmax", //58
     Serial.print(myText[50]); Serial.println (twmin); Serial.println(myText[19]);//55
     
     Serial.print(myText[45]); Serial.println (gazmax); Serial.println(myText[48]);//55
      
      }
 if ((bluetoothCommand==98)||(NRF_message==98)||(I2C_message==98))// обнуляємо до заводських установок з стиранням унікального і присвоєнням нового
      {  
          EEPROM.write(0, 0); 
          Serial.println(myText[42]);
          delay(500);
          asm volatile("jmp 0x00");
      }
 
if (bluetoothCommand==99)// виводимо унікальний номер модуля (згенерований під час першої прошивки мікроконтролера і запуску
      {  
                        byte m=EEPROM.read(300); delay(5);
                        byte H=EEPROM.read(301); delay(5);
                        byte D=EEPROM.read(302); delay(5);
                        byte M=EEPROM.read(303); delay(5);
                        byte Y=EEPROM.read(304); delay(5);
                        Serial.print(myText[12]);
                        Serial.print(Y);Serial.print(M);Serial.print(D);Serial.print(H);Serial.println(m);
                       
      
      }
  
if((bluetoothCommand>=11000)&&(bluetoothCommand<=11059))      // корекція і встановлення дня хвилин
{minute=bluetoothCommand-11000;
Wire.beginTransmission(DS1307);
   Wire.write(0x1);
   Wire.write(decToBcd(minute));
   Wire.endTransmission();}
if((bluetoothCommand>=11100)&&(bluetoothCommand<=11123))      // корекція і встановлення години
{hour=bluetoothCommand-11100;
Wire.beginTransmission(DS1307);
   Wire.write(0x2);
   Wire.write(decToBcd(hour));
   Wire.endTransmission();}

if((bluetoothCommand>=11201)&&(bluetoothCommand<=11231))      // корекція і встановлення дня місяця
{dayOfMonth=bluetoothCommand-11200;
Wire.beginTransmission(DS1307);
   Wire.write(0x4);
   Wire.write(decToBcd(dayOfMonth));
   Wire.endTransmission();}

if((bluetoothCommand>=11301)&&(bluetoothCommand<=11312))      // корекція і встановлення номера місяця (01-12)
{month=bluetoothCommand-11300;
Wire.beginTransmission(DS1307);
   Wire.write(0x5);
   Wire.write(decToBcd(month));
   Wire.endTransmission();}

if((bluetoothCommand>=11321)&&(bluetoothCommand<=11399))      // корекція і встановлення року (21-99)
{year=bluetoothCommand-11300;
Wire.beginTransmission(DS1307);
   Wire.write(0x6);
   Wire.write(decToBcd(year));
   Wire.endTransmission();}
 // обнулюємо всі команди після їх виконання
 bluetoothCommand=0;
 NRF_message=0;
I2C_message=0;
} 
 