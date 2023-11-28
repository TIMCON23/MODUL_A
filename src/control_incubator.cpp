
/*
 * функція контролю параметрів заданих в інкубаторі та сключення/
 * виключення відповідних релейних модулів зовнішних девайсів
 * крім режиму PID
 * темпереатура регілюється автоматично
 */

#include "main.h" // підключаємо головний файл з назвами функцій

void incubator_Control()       {
   Serial.println();
     
  Serial.println(myText[17]);
  if ((data.t <= Tmin)&&(flag_sensor_DHT22 == false)&&(flag_Rele1 == false))
      { digitalWrite(RELAY1_PIN, LOW );// включення опалення (тепловентилятор або нагріву/охолодження води в системі радіаторів )
        pcf8574.digitalWrite(P7, LOW);// включаємо циркуляційний насос газового котла (додатковий нагрів)
          };    
          
  if ((data.t >= Tmax)&&(flag_sensor_DHT22 == false)&&(flag_Rele1 == false))
      { digitalWrite(RELAY1_PIN, HIGH);
     
      }; 

if ((data.t >(5+Tmax)) && (flag_sensor_DHT22 == false) && (flag_Rele1 == false))
  {  digitalWrite(RELAY1_PIN, LOW);// включаємо d4 циркуляційний насос  для охолодження (через радіатор)
     if (!data.flag_pcf8574ReleP7) pcf8574.digitalWrite(P7, HIGH); // виключаємо додатковий нагрів через газовий котел(твердопаливний котел)
 };    
  if ((data.t <Tmax)&&(flag_sensor_DHT22 == false) && (flag_Rele1 == false))
  { digitalWrite(RELAY1_PIN, HIGH);
 };
 
  if ((data.h >= Hmax)&&(flag_sensor_DHT22 == false) && (flag_Rele3 == false))
    { digitalWrite(RELAY3_PIN, LOW);// включаємо d6 витяжну вентиляцію
    };   
  if ((data.h <= Hmin)&&(flag_sensor_DHT22 == false)&&(flag_Rele3 == false))
    { digitalWrite(RELAY3_PIN, HIGH);};
  
if((data.gaz >= gazmax) && (flag_Rele3 == false))
  { digitalWrite(RELAY3_PIN, LOW);  };              // включаємо витяжку для провітрювання
if((data.gaz <= gazmax) && (flag_Rele3 == false))
  {digitalWrite(RELAY3_PIN, HIGH);}                // виключаємо провітрювання
if ((flag_power == true)&&(digitalRead(2)==HIGH))
 {Serial.println(myText[9]);
   };
if ((flag_power == true)&&(digitalRead(2)==LOW))
 {  flag_power = false;};
    
   
if ((flag_alarm == true)&&(digitalRead(3)==HIGH))
 {Serial.println(myText[8]); flag_alarm = false;};
    
if ((flag_alarm == true)&&(digitalRead(3)==LOW)){flag_alarm = false; };
  

if (SENSORWATER_PIN==LOW){ Serial.println(myText[6]);};
   
    
if (SENSORFOOD_PIN==HIGH) {Serial.println(myText[7]);};
   
  if ((SENSORWATER_PIN==1)&&(flag_Watter_Box==true)&&(data.flag_pcf8574RelePO==false))
 { pcf8574.digitalWrite(P0, LOW);                // включаємо насос скважини для накачки води (порти розширення налаштовані на 
                                                  // HIGH виключати можна командою LOW? таймер налаштовується через блютуз і кнопки
  timer3=millis()+(timer3*60*1000); // робимо таймер з даного моменту
  startPump=1; // повідомляємо про включення насосу
  }; //замінити на таймер або на сигнал від досягнення верхнього рівня баку(?)
 
 if((SENSORFOOD_PIN==0)&&(flag_Food_Box==true)&&(data.flag_pcf8574ReleP4==false))
   {pcf8574.digitalWrite(P4, LOW); // включення редуктора-мотора для подачі корму по трубопроводі (кінцеві вимикачі при досягненні рівня корму) а в платі таймер для переведення відключення
    timer4=millis()+(timer4*60*1000); // робимо таймер з даного моменту
    startFood_motor=1; // мотора для подачі корму
//    ton;
  }; 
 
        
if ((flag_alarm)&&(data.flag_pcf8574ReleP5==false))
{  pcf8574.digitalWrite(P5, LOW);   // камера відеонагляду в приміщення (умова - порушення сигналізації або команда 11 
 
    uint32_t myTimer1;
    int period = 180000; // запис на 3 хв

  if (millis() - myTimer1 >= period) {   // ищем разницу (500 мс)
    myTimer1 += period;              // сброс таймера
    pcf8574.digitalWrite(P5, HIGH);
  }
}
  



 }