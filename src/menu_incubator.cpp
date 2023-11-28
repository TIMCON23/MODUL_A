//частина коду для меню і LCD екрана

#include "main.h" // підключаємо головний файл з назвами функцій

void read_readKey ()      {                  
        readKey = analogRead(A6);
    if (readKey < 790) {
      delay(100);
      readKey = analogRead(A6);
     }                
}
// збереження даних
void save_setting()       {
        button = 0;
        lcd.setCursor(0, 0);
        lcd.print(myText[30]);
        lcd.setCursor(0, 1);
        lcd.print(myText[53]);
        delay(1000);
         button = 0;
         activeButton = 1; // вихід в меню
        asm volatile("jmp 0x00");
        
        }    
    //Функция выводящая на экран два пункта меню, они будут менятся при прокрутке
void mainMenuDraw()       {
  Serial.print(menuPage);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
  if (menuPage == 0) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
  } else if (menuPage > 0 and menuPage < maxMenuPages) {
    lcd.setCursor(15, 1);
    lcd.write(byte(2));
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  } else if (menuPage == maxMenuPages) {
    lcd.setCursor(15, 0);
    lcd.write(byte(1));
  }
}
    //Функция рисуящая курсор в соответствии с выбранным пунктом меню
void drawCursor()         {
  for (int x = 0; x < 2; x++) {
    lcd.setCursor(0, x);
    lcd.print(" ");
  }
 
  // The menu is set up to be progressive (menuPage 0 = Item 1 & Item 2, menuPage 1 = Item 2 & Item 3, menuPage 2 = Item 3 & Item 4), so
  // in order to determine where the cursor should be you need to see if you are at an odd or even menu page and an odd or even cursor position.
  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is even and the cursor position is even that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is even and the cursor position is odd that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {  // If the menu page is odd and the cursor position is even that means the cursor should be on line 2
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {  // If the menu page is odd and the cursor position is odd that means the cursor should be on line 1
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}
void operateMainMenu()    {
  activeButton = 0;
  while (activeButton == 0) {
    
    read_readKey ();
    button = evaluateButton(readKey);
    switch (button) {
      case 0: //Если ничего не нажато
        break;
      case 1:  //Выполнять действие если нажата "назад"
        button = 0;
        switch (cursorPosition) { //Переходить в то меню, на котором стоит курсор
          case 0:
            menuItem1(); 
            break;
          case 1:
           menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          case 3:
             menuItem4();
            break;
    //      case 4:
    //        menuItem5();
    //        break;
     //     case 5:
     //       menuItem6();
     //       break;
          }
        activeButton = 1;
        mainMenuDraw();
        drawCursor();
        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
 
        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
 
        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
 
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
 
        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
 
        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        mainMenuDraw();
        drawCursor();
        activeButton = 1;
        break;
    }
  }
}
    //Эта функция вызывается когда нажата какая-либо кнопка и путем считывания напряжения на A0, определить какая именно кнопка нажата
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // Right
  } else if (x < 195) {
    result = 2; // Up
  } else if (x < 400) {
    result = 3; // Down
  } else if (x < 600){
    result = 4; // Left
  } else if (x < 800) {
    result = 5; // Set
  }
  return result;
}
    //Встановлення стрілки і курсора на години, день місяця
void drawInstruction5()   {// стрілка на 5 символ нижнього рядка
  lcd.setCursor(0, 1);
  lcd.print(myText[51]);
  lcd.setCursor(5, 1);
  lcd.print(myText[52]);
}
    //Функції, встановлення указника(стрілки)при налаштуваннях параметрів через меню
    // курсор на хвилинах, 
void drawInstruction2()   { //на 10 символ нижнього рядка
  lcd.setCursor(0, 1);
 lcd.print(myText[51]);// чистимо нижню лінійку
  lcd.setCursor(10, 1);           // ставимо курсор на 10 ячейці щоб міняти хвилини або місяці
  lcd.print(myText[52]); // Up arrow
}
    //Установка курсора на рік,будильник
void drawInstruction14()   { //на 14 символ нижнього рядка
  lcd.setCursor(0, 1);
  lcd.print(myText[51]);
  lcd.setCursor(14, 1);
  lcd.print(myText[52]);
}
void Mane_menu() {        // Основне меню: виводить усю інформацію про стан об'єкту
  activeButton = 0;
  while (activeButton == 0) {
          read_readKey ();
          button = evaluateButton(readKey);
            switch (button) {
            case 5:  // Якщо натиснута кнопка "SELECT" в меню для налаштувань (але на останньому рядку циклу)
            button = 0;
            activeButton = 1;
            break;
        
        default:
      // усі функції контролю і моніторингу тут:
       
        if  (millis() - timer1 >= PERIOD1)          // кожних 5 хв перевіряємо стан
     {
        GET_DateTime();
        sensors_read();
        send_Lcd_Clock();
        send_LCD_sensors();
        parameter_control();
        send_dataI2C();
      do {
       timer1 += PERIOD1;
      if (timer1 < PERIOD1) break;  // переполнение uint32_t
     } while (timer1 < millis() - PERIOD1); // защита от пропуска шага
      }
  
  if  (millis() - timer2 >= PERIOD2)          // кожних 5 хв перевіряємо стан
     {
        parameter_control();
    
        send_radio();
  do {
       timer2 += PERIOD2;
      if (timer2 < PERIOD2) break;  // переполнение uint32_t
     } while (timer2 < millis() - PERIOD2); // защита от пропуска шага
      }
       
       
    
      if (Serial.available() > 0)
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
     
      if((NRF_message>0)||(I2C_message>0))read_bluetoothComand();
      
     }
    
  }
  }
void menuItem1() {        // Перше меню : налаштування годинника через кнопки з передачею у пам'ять годинника
  activeButton = 0;
  clockPos = 1;
  lcd.clear();            // чистимо екран
  send_Lcd_Clock();        //друкуємо дату і час
  lcd.setCursor(0, 1);    //курсор на нижній рядок на 10 ячейці
  lcd.print(myText[52]);        //  стрілка на 10 ячейці
 
                          // цикл для налаштування годинника (без секунд)
 while (activeButton == 0) {
    read_readKey();
    button = evaluateButton(readKey);
         //Позиція курсора, : 1-день року, 2-місяць року, 3-номер року,4- година, 5-хвилина 
  switch (button) {
   case 2: // якщо нажали "Up"
        if (clockPos==1)      {
            button = 0;
              if (dayOfMonth==31)dayOfMonth=0;
              else dayOfMonth = dayOfMonth + 1;// збільшуємо день місяця
                dayOfMonth = constrain(dayOfMonth,0,31);
                lcd.setCursor(0,0);
            
              if (dayOfMonth >=0 && dayOfMonth < 10) {lcd.print(F("0")); lcd.print(dayOfMonth);}
              else lcd.print(dayOfMonth);
        }
       
        else if (clockPos==2) {
                button = 0;
             if (month==12) month=0;
             else month = month + 1; // збільшуємо номер місяця
                month = constrain(month,0, 12);
              lcd.setCursor(3,0);
               if (month >=0 && month < 10) {lcd.print(F("0")); lcd.print(month);}
                else lcd.print(month);
        }
        
        else if (clockPos==3) {
             button = 0;
              if (year==99) year=21;
              else year = year + 1; // збільшуємо номер місяця
              year = constrain(year,21, 99);
              lcd.setCursor(6,0);
              lcd.print(year);
          }
         
        else if (clockPos==4) {
              button = 0;
              if (hour==23) hour=0;
              else hour = hour + 1;
              hour = constrain(hour,0, 24);
              lcd.setCursor(11,0);
           
                if (hour >=0 && hour < 10) {lcd.print(F("0")); lcd.print(hour);}
                else lcd.print(hour);// виводимо години
          }
      
        else if (clockPos==5) {
              button = 0;
              if (minute==59) minute=0;
              else minute = minute + 1;
              minute = constrain(minute,0,60);
              lcd.setCursor(14,0);
               if (minute >=0 && minute < 10) {lcd.print(F("0")); lcd.print(minute);}
                else lcd.print(minute);// виводимо хвилини на екрані 
          } 
          break;
       
   case 3: //якщо нажата кнопка DOWN - зменшуємо на 1 цифру хвилини
        if (clockPos==1)     {
            button = 0;
              if (dayOfMonth==31)dayOfMonth=0;
              else dayOfMonth = dayOfMonth - 1;// збільшуємо день місяця
                dayOfMonth = constrain(dayOfMonth,0,31);
                lcd.setCursor(0,0);
              
              if (dayOfMonth >=0 && dayOfMonth < 10) {lcd.print(F("0")); lcd.print(dayOfMonth);}
              else lcd.print(dayOfMonth);
        }
       
       else if (clockPos==2) {
            button = 0;
             if (month==12) month=0;
             else month = month - 1; // збільшуємо номер місяця
                month = constrain(month,0, 12);
              lcd.setCursor(3,0);
                if (month >=0 && month < 10) {lcd.print(F("0")); lcd.print(month);}
                else lcd.print(month);
        }
        
       else if (clockPos==3) {
             button = 0;
             if (year==21) year=99;
              else
              year = year - 1; // збільшуємо номер місяця
              year = constrain(year,21, 99);
              lcd.setCursor(6,0);
              lcd.print(year);
          }
         
       else if (clockPos==4) {
              button = 0;
              if (hour==23) hour=0;
              else hour = hour - 1;
              hour = constrain(hour,0, 24);
              lcd.setCursor(11,0);
              if (hour >=0 && hour < 10) {lcd.print(F("0")); lcd.print(hour);}
                else lcd.print(hour);// виводимо години
          }
      
       else if (clockPos==5) {
              button = 0;
              if (minute==59) minute=0;
              else minute = minute - 1;
              minute = constrain(minute,0,60);
              lcd.setCursor(14,0);
                if (minute >=0 && minute < 10) {lcd.print(F("0")); lcd.print(minute);}
                else lcd.print(minute);// виводимо хвилини на екрані 
          }
        break;  
            //Позиція курсора згідно clockPos: 1(0)-день року, 2(3)-місяць року, 3(6)-номер року,4(11)- година, 5(14)-хвилина 
   case 4: // Если нажата кнопка влево, смотрим где стоит курсор в данный момент и переставляем левее
        if (clockPos==5){ 
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(11, 1);
            lcd.print(myText[52]);
            clockPos=4;}
        else if (clockPos==4){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(6, 1);
             lcd.print(myText[52]);
            clockPos=3;}
        else if (clockPos==3){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(3, 1);
             lcd.print(myText[52]);
            clockPos=2;}
        else if (clockPos==2){
            lcd.setCursor(0, 1);
           lcd.print(myText[51]);
            lcd.setCursor(0, 1);
            lcd.print(myText[52]);
            clockPos=1;}
        else if (clockPos==1){
            button = 0;
         activeButton = 1;}
        break;
          
    
   case 1: // Если нажата кнопка вправо, смотрим где стоит курсор в данный момент и переставляем правее
       if (clockPos==1){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(3, 1);
            lcd.print(myText[52]);
            clockPos=2;}
       else if (clockPos==2){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(6, 1);
            lcd.print(myText[52]);
            clockPos=3;}
       else if (clockPos==3){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(11, 1);
            lcd.print(myText[52]);
            clockPos=4;}
       else if (clockPos==4){
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(14, 1);
             lcd.print(myText[52]);
            clockPos=5;} 
       else if (clockPos==5){
            
          lcd.setCursor(0, 0);
          button = 0;
          activeButton = 1; // вихід в меню
            }

            
       break;
   case 5:  // Якщо нажата select  - зберігаємо установлені значення дати , години і хвилини 
       
        // записуємо дані в годинник
        Wire.beginTransmission(DS1307);
        Wire.write(0x1);
        Wire.write(decToBcd(minute)); // зберігаємо змінені годину і хвилину
        Wire.endTransmission();
        delay(10);
        
        Wire.beginTransmission(DS1307);
        Wire.write(0x2);
        Wire.write(decToBcd(hour)); // зберігаємо змінені годину і хвилину
        Wire.endTransmission();
        delay(10);
       
        Wire.beginTransmission(DS1307);
        Wire.write(0x4);
        Wire.write(decToBcd(dayOfMonth)); // зберігаємо змінені годину і хвилину
        Wire.endTransmission();
        delay(10);
        
        Wire.beginTransmission(DS1307);
        Wire.write(0x5);
        Wire.write(decToBcd(month)); // зберігаємо змінені годину і хвилину
        Wire.endTransmission();
        delay(10);
        
         Wire.beginTransmission(DS1307);
        Wire.write(0x6);
        Wire.write(decToBcd(year)); // зберігаємо змінені годину і хвилину
        Wire.endTransmission();
        delay(10);
        save_setting();
   
   break; // вихід у види меню після налаштування дати
  }
 }
}
void menuItem2() {        // Друге меню: активація роботи лічильника днів і параметрів утримання
  activeButton = 0;
  clockPos = 1;
 
  lcd.clear();            // чистимо екран
  
  lcd.setCursor(0, 0);    //
  lcd.print(F("Day:")); lcd.print(data.routing1);lcd.print(F("    "));
  
  
  lcd.setCursor(4, 1);
 lcd.print(myText[52]);
  lcd.print(F("   next>"));
   while (activeButton == 0) {
    read_readKey();
      button = evaluateButton(readKey);
      switch (button) {
  case 2:  // якщо нажата кнопка "UP" - додавання до змінних
        if(clockPos == 1)      {  // коректуємо день утримання (день утримання при запуску таймеру рахунку днів утримання модуля)      
          button = 0;
          if (correctDey ==99) correctDey=1;
            else correctDey = correctDey + 1;              //  збільшуємо максимально допустиму корекцію на 1 день
            correctDey = constrain(correctDey,1,99);
             lcd.setCursor(4,0);
          lcd.print(myText[52]);
            lcd.setCursor(4,0);
            lcd.print(correctDey);
            }
        else if(clockPos == 2) {  // крутимо режими утримання по цифрах режимів на утриманні
              button = 0;
                if(data.routine_feeding>9) data.routine_feeding=1;
                data.routine_feeding = data.routine_feeding + 1;              
                data.routine_feeding = constrain(data.routine_feeding,1,9);

                lcd.setCursor(9,0);
                read_routine_feeding();
                 
        }
        else if(clockPos == 3) {  // вибираємо к-сть птиці на утриманні
          button = 0;
         
            if (data.number_feeding ==999) data.number_feeding=1;
                data.number_feeding = data.number_feeding + 1;              //  збільшуємо  на одиницю
                data.number_feeding = constrain(data.number_feeding,1,999);
               
                lcd.setCursor(4,0);
                lcd.print(data.number_feeding);
               }
        else if(clockPos == 4) {  // збільшуємо загальну к-сть днів утримання
       button = 0;
             if (all_feeding ==999) all_feeding=10;
                all_feeding = all_feeding + 1;              //  збільшуємо  на одиницю
                all_feeding = constrain(all_feeding,10,999);
               
                lcd.setCursor(13,0);
                lcd.print(all_feeding);
      }
     break;
  
  case 3:  // якщо нажата кнопка "Down" - віднімання від змінних
       if(clockPos == 1) { 
                button = 0;
              
              if (correctDey==1) data.dey_feeding=99;
                correctDey = correctDey - 1;              //  зменшуємо на одиницю
                correctDey = constrain(correctDey,1,99);
                lcd.setCursor(4,0);
               lcd.print(myText[52]);
                lcd.setCursor(4,0);
                lcd.print(correctDey);
                }
       else if(clockPos == 2)  {   //змінюємо режими утримання
                button = 0;
                
              if (data.routine_feeding==0) data.routine_feeding=9;
                data.routine_feeding = data.routine_feeding - 1;              //  збільшуємо на одиницю
                data.routine_feeding = constrain(data.routine_feeding,1,9);
               
                lcd.setCursor(9,0);
                 read_routine_feeding();
                               
         } 
       else if(clockPos == 3)  {   // зменшуємо к-сть птиці на утриманні
          button = 0;
         
            if ( data.number_feeding ==1)  data.number_feeding=999;
                 data.number_feeding =  data.number_feeding - 1;              //  зменшуємо на одиницю
                 data.number_feeding = constrain(data.number_feeding,1,999);
                lcd.setCursor(4,0);
               
                lcd.print(data.number_feeding);
                }
       else if(clockPos == 4)  {   // зменшуємо загальну к-сть днів утримання
              button = 0;
                if (all_feeding ==999) all_feeding=10;
                all_feeding = all_feeding - 1;              //  зменшуємо на одиницю
                all_feeding = constrain(all_feeding,10,999);
              
                lcd.setCursor(13,0);
                lcd.print(all_feeding);
      }
     break;
  
  case 4: // якщо нажата кнопка "LEFT", дивимось де курсор в даний момент и переставляємо лівіше
       if  (clockPos==2)      {
            lcd.setCursor(0, 1);
           lcd.print(myText[51]);
            lcd.setCursor(4, 1);
           lcd.print(myText[52]);
            clockPos=1;}
       else if (clockPos==4)  {
            lcd.setCursor(0, 1);
           lcd.print(myText[51]);
            lcd.setCursor(4, 1);
            lcd.print(myText[52]);
            clockPos=3;}
       else if (clockPos==3)  {
            lcd.setCursor(0, 0);
          lcd.print(myText[51]);
            lcd.setCursor(0, 0);
            lcd.print("Day:"); lcd.print(data.dey_feeding);lcd.print("    ");
            read_routine_feeding();
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(9, 1);
            lcd.print(myText[52]);
            clockPos=2;}
     break;
     
  case 1: //  якщо нажата кнопка "RIGTH", дивимось де курсор в даний момент и переставляємо вправо
       if (clockPos==1){
          lcd.setCursor(0, 1);
          lcd.print(myText[51]);
          lcd.setCursor(9, 1); // стаємо під назвою птахів
          lcd.print(myText[52]);
          clockPos=2;}
       else if (clockPos==2)  {
          lcd.setCursor(0, 0);
          lcd.print(F("Num ")); lcd.print(data.number_feeding);lcd.setCursor(9, 0);
          lcd.print(F("All ")); lcd.print(all_feeding);lcd.print(F(" "));
          lcd.setCursor(0, 1);
         lcd.print(myText[51]);
          lcd.setCursor(4, 1);
          lcd.print(myText[52]);
          clockPos=3;}
       else if (clockPos==3)  {
          lcd.setCursor(0, 1);
          lcd.print(myText[51]);
          lcd.setCursor(13, 1);
         lcd.print(myText[52]);
          clockPos=4;
          }
       else if (clockPos==4)  {
          button=0;
         activeButton =1;
        
         }
    break;
    
   
  
   
   
   case 5:  // якщо нажата кнопка "select"
        
        flag_Startfeeding=true;
       
       EEPROM.update(6, 1);//ставимо мітку що лічильник включено і запущено відрахунок днів
       EEPROM.put(280,all_feeding);
       EEPROM.put(42,correctDey);
       EEPROM.put(40,data.number_feeding);  
       EEPROM.put(201,data.routine_feeding);  
       save_setting();
       
       break;
   }
  }
}                        //читаємо дані з сенсорів і датчиків і їх обрізаємо та фільтруємо)
void menuItem3() {        // Третє меню: налаштування параметрів контролю максимумів і мінімумів температури,(в тому числі коефіцієнтів PID)
  activeButton = 0;
  clockPos = 1;
  lcd.clear();            // чистимо екра
 
//int  Tmax,Tmin,Hmin,Hmax,twmax,gazmax;

lcd.setCursor(0, 0);    //
lcd.print(myText[54]); lcd.print(Tmax);lcd.print(F("  "));
lcd.print(myText[55]); lcd.print(Tmin);lcd.print(F("  "));

lcd.setCursor(5, 1);
lcd.print(myText[52]);
lcd.print(F("   next>>"));
 while (activeButton == 0) {
    read_readKey();
    button = evaluateButton(readKey);
    switch (button) {
     
     case 2: // якщо нажали "Up"
        if (clockPos==1)      {
                button = 0;
                if (Tmax ==99)Tmax=26;
                Tmax = Tmax + 1;                 //  збільшуємо максимально допустиму температуру на 1 градус
                Tmax = constrain(Tmax,26,99);
              
                lcd.setCursor(5,0);
                lcd.print(Tmax);
                }
        else if (clockPos==2) {
                button = 0;
                if (Tmin ==25)Tmin=1;
                Tmin = Tmin + 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                Tmin = constrain(Tmin,1,25);
                
                lcd.setCursor(14,0);
                lcd.print(Tmin);
                }
        else if (clockPos==3) {
                 button = 0;
              if (Hmax ==99)Hmax=51;
                  Hmax = Hmax + 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                  Hmax = constrain(Hmax,51,99);
                  lcd.setCursor(14,0);
                  lcd.print(Hmax);
                }
        else if (clockPos==4) {
                  button = 0;
               if (Hmin ==49)Hmin=1;
                  Hmin = Hmin + 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                  Hmin = constrain(Hmin,1,49);
                  lcd.setCursor(5,0);
                  lcd.print(Hmin);
                  }
        else if (clockPos==5) {
                button = 0;
                if (twmax ==69)twmax=15;
                twmax = twmax + 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                twmax = constrain(twmax,15,69);
              
                lcd.setCursor(5,0);
                lcd.print(twmax);
                }
        else if (clockPos==6) {
                button = 0;
                if (gazmax ==999)gazmax=101;
                gazmax = gazmax + 50;              //  збільшуємо максимально допустиму температуру на 1 градус
                gazmax = constrain(gazmax,101,999);
              
                lcd.setCursor(13,0);
                lcd.print(gazmax);
                }
       break;
     
    case 3: //якщо нажата кнопка DOWN - зменшуємо на 1 градус
        if (clockPos==1)      {
                button = 0;
                if (Tmax ==99)Tmax=26;
                Tmax = Tmax - 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                Tmax = constrain(Tmax,26,99);
             
                lcd.setCursor(5,0);
                lcd.print(Tmax);
                 }
        else if (clockPos==2) {
                button = 0;
                if (Tmin ==25)Tmin=1;
                Tmin = Tmin - 1;              //  збільшуємо максимально допустиму температуру на 1 градус
                Tmin = constrain(Tmin,1,25);
              
                lcd.setCursor(14,0);
                lcd.print(Tmin);
                }
        else if (clockPos==4) {
                button = 0;
                if (Hmin ==1)Hmin=49;
                Hmin = Hmin - 1;              //  зменшуємо мінімально допустиму температуру на 1 градус
                Hmin = constrain(Hmin,1,49);
               
                lcd.setCursor(14,0);
                lcd.print(Hmin);
                }
        else if (clockPos==3) {
                button = 0;
                if (Hmax ==51)Hmax=99;
                Hmax = Hmax - 1;              //   зменшуємо максимально допустиму температуру на 1 градус
                Hmax = constrain(Hmax,51,99);
                
                lcd.setCursor(5,0);
                lcd.print(Hmax);
                }
        else if (clockPos==5) {
                button = 0;
                if (twmax ==15)twmax=69;
                twmax = twmax - 1;              //  зменшуємо максимально допустиму температуру на 1 градус
                twmax = constrain(twmax,15,69);
                  lcd.setCursor(5,0);
                lcd.print(twmax);
                }
        else if (clockPos==6) {
                button = 0;
                if (gazmax <=101)gazmax=999;
                gazmax = gazmax - 50;              //  збільшуємо максимально допустиму температуру на 1 градус
                gazmax = constrain(gazmax,101,999);
                     lcd.setCursor(13,0);
                lcd.print(gazmax);
                }
      break;
  
    case 1: // Если нажата кнопка RIGTH, вправо, смотрим где стоит курсор в данный момент и переставляем правее
        if (clockPos==1){
            drawInstruction14();
            clockPos=2;}
        else if (clockPos==2) {
            lcd.setCursor(0, 0);
            lcd.print(F("                "));
            lcd.setCursor(0, 0);
            lcd.print(myText[56]); lcd.print(Hmax);lcd.print(F("  "));
            lcd.print(myText[57]); lcd.print(Hmin);lcd.print(F("  "));
           
            drawInstruction5();
            
            clockPos=3;}
        else if (clockPos==3) {
            drawInstruction14();
            lcd.print(">>");
            clockPos=4;
            }
        else if (clockPos==4) {
            lcd.setCursor(0, 0);
           lcd.print(myText[51]);
            lcd.setCursor(0, 0);
            lcd.print(myText[58]); lcd.print(twmax);lcd.print(F(" "));
            lcd.print(myText[59]); lcd.print(gazmax);lcd.print(F("  "));
            drawInstruction5();
           
             clockPos=5;}
        else if (clockPos==5) {
            lcd.setCursor(0, 1);
            lcd.print(myText[51]);
            lcd.setCursor(13, 1);
            lcd.print(myText[52]);
            lcd.print("><");
            clockPos=6;
            }
        else if (clockPos==6) {
               save_setting();
             }
      break;
        
    case 4:  // Если нажата кнопка "left"
        if  (clockPos==2){
            drawInstruction5();
            clockPos=1;}
       else if (clockPos==4){
           drawInstruction5();
            clockPos=3;}
       else if (clockPos==6){
            drawInstruction5();
            clockPos=5;}
       else if (clockPos==5){
            lcd.setCursor(0, 0);
            lcd.print(myText[51]);
            lcd.setCursor(0, 0);
            lcd.print(myText[56]); lcd.print(Hmax);lcd.print("  ");
            lcd.print(myText[57]); lcd.print(Hmin);lcd.print("  ");
            
            drawInstruction14();
            clockPos=4;}
       else if (clockPos==3){
            lcd.setCursor(0, 0);
            lcd.print(myText[51]);
            lcd.setCursor(0, 0);
             lcd.print(myText[54]);lcd.print(Tmax);lcd.print(F("  "));
             lcd.print(myText[55]); lcd.print(Tmin);lcd.print(F("  "));
            drawInstruction14();
            clockPos=2;}
       else if (clockPos==1){
            activeButton = 1;}
      
      break;
     
     case 5:  // Если нажата кнопка "set"
                   
           EEPROM.put(7,Tmin);
           EEPROM.put(9, Tmax);                    // перезаписуємо в пам'ять (якщо там інші дані) старший байт в ячейку 1?
           EEPROM.put(11, Hmin);                   // перезаписуємо в пам'ять (якщо там інші дані) старший байт в ячейку 1?
           EEPROM.put(13, Hmax);                 // перезаписуємо в пам'ять (якщо там інші дані) старший байт в ячейку 1?
           EEPROM.put(23, gazmax);                      // перезаписуємо в пам'ять (якщо там інші дані) старший байт в ячейку 1?
           EEPROM.put(15, twmax);                   // перезаписуємо в пам'ять (якщо там інші дані) старший байт в ячейку 1?
           
            save_setting();  
            break;
   }
  }
}
void menuItem4() {        // четверте меню: налаштування таймерів для приладів
  activeButton = 0;
  clockPos = 1;
  lcd.clear();            // чистимо екра
 
lcd.setCursor(0, 0); 
lcd.print(F("PUMB")); lcd.print(timer3);
lcd.setCursor(9, 0);
lcd.print(F("FOD")); lcd.print(timer4);

lcd.setCursor(4, 1);
lcd.print(myText[52]);
lcd.print(F(" minute >>"));
 while (activeButton == 0) {
    read_readKey();
    button = evaluateButton(readKey);
    switch (button) {
     
     case 2: // якщо нажали "Up"
        if (clockPos==1)      {
                button = 0;
                if (timer3 ==1440)timer3=1;
                timer3 = timer3 + 1;                 //  збільшуємо максимально допустиму температуру на 1 градус
                timer3 = constrain(timer3,1,1440);
              
                lcd.setCursor(4,0);
                lcd.print(timer3);
                }
       
        else if (clockPos==2) {
               button = 0;
                if (timer4 ==1440)timer4=1;
                timer4 = timer4 + 1;                 //  збільшуємо максимально допустиму температуру на 1 градус
                timer4 = constrain(timer4,1,1440);
              
                lcd.setCursor(12,0);
                lcd.print(timer4);
                }
  
       break;
     
    case 3: //якщо нажата кнопка DOWN - зменшуємо на 1 градус
        if (clockPos==1)      {
                button = 0;
                if (timer3 ==1)timer3=1440;
                timer3 = timer3 - 1;                 //  збільшуємо максимально допустиму температуру на 1 градус
                timer3 = constrain(timer3,1,1440);
              
                lcd.setCursor(4,0);
                lcd.print(timer3);
                }
        else if (clockPos==2) {
                 button = 0;
                if (timer4 ==1)timer4=1440;
                timer4 = timer4 - 1;                 //  збільшуємо максимально допустиму температуру на 1 градус
                timer4 = constrain(timer4,1,1440);
              
                lcd.setCursor(12,0);
                lcd.print(timer4);
                }
  
      break;
  
    case 1: // Если нажата кнопка RIGTH, вправо, смотрим где стоит курсор в данный момент и переставляем правее
        if (clockPos==1){
           lcd.setCursor(0, 1);
          lcd.print(myText[51]);
          lcd.setCursor(12, 1);
          lcd.print(myText[52]);
            clockPos=2;}
           
        else if (clockPos==2) {
            
           activeButton = 1;}
             
      break;
        
    case 4:  // Если нажата кнопка "left"
        if  (clockPos==2){
           lcd.setCursor(0, 1);
          lcd.print(myText[51]);
          lcd.setCursor(4, 1);
          lcd.print(myText[52]);
            clockPos=1;}
     
   
       else if (clockPos==1){
            activeButton = 1;}
      
      break;
     
     case 5:  // Если нажата кнопка "set"
                   
           EEPROM.put(100,timer3);// перезаписуємо в пам'ять к-сть хвилин таймера насоса води в бочку
           EEPROM.put(105,timer4);// перезаписуємо в пам'ять к-сть хвилин таймера мотора кормоподачі
           save_setting();  
            break;
   }
  }
}