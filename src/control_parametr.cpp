
/*
 * функція контролю показників середовища відповідно до обраного режиму інкубації (обраної породи (
 * параметри задаються автоматично для основних порід птахів  
 * або вручну якщо таких птахів немає в списку)
 * в функції перевіряються і виводяться для моніторингу параметри інкубації
 * 
 */
#include "main.h" // підключаємо головний файл з назвами функцій


void parameter_control ()   {   
  Serial.println(myText[25]);// встановлюємо режим утримання
 if((data.routine_feeding>0)&&(data.routine_feeding<=8))
  {
    switch (data.routine_feeding){
     case 1: //  режим утримання бройлера
    if(data.dey_feeding<=3)   // якщо днів утримання менше 10-ти
   {Tmax=35;        // встановлюємо темп.максимальну в приміщенні
    Tmin=25;         // встановлюємо темп.мінімальну в приміщенні
    Hmax=65;
    Hmin=45;
    twmax = 25;
    gazmax =150;
   
   }
   
   else  if
   (data.dey_feeding<=5)
    {Tmax=33;
    Tmin= 25;
    Hmax=75;
    Hmin=55;
    twmax = 25;
    gazmax =150;
    }
  else if 
   (data.dey_feeding<=7)
    {Tmax=31;
    Tmin= 25;
    Hmax=75;
    Hmin=55;
    twmax = 25;
    gazmax =200;
    }
    
     else if
    (data.dey_feeding<=10)
    {Tmax=28;
    Tmin= 23;
    Hmax=75;
    Hmin=55;
    twmax = 23;
   gazmax =200;
    }
    else if
    (data.dey_feeding<=14)
    {Tmax=26;
    Tmin= 22;
    Hmax=75;
    Hmin=55;
    twmax = 21;
    gazmax =250;
    } 
    
   else if
    (data.dey_feeding<=21)
    {Tmax=24;
    Tmin= 21;
    Hmax=75;
    Hmin=55;
    twmax = 20;
    gazmax =300;
    } 
   else
     {Tmax=18;
    Tmin= 15;
    Hmax=75;
    Hmin=55;
    twmax = 18;
    gazmax =350;
     }  
   break;
 case 2:// параметри утримання індиків
    if(data.dey_feeding<=7)
   { Tmax=36;
    Tmin= 28;
    Hmax=70;
    Hmin=55;
    twmax = 25;
    gazmax =300;
     //повне освітлення (24 години на добу)
    }
    else if(data.dey_feeding<=14)
   {Tmax=30;
    Tmin= 25;
    Hmax=75;
    Hmin=55;
    twmax = 25;
    gazmax =300;
    //повне освітлення (24 години на добу)
    }
    else if(data.dey_feeding<=21)
   {Tmax=25;
    Tmin= 22;
    Hmax=75;
    Hmin=55;
    twmax = 23;
   gazmax =300;
   
    }
   else
   { Tmax=20;
    Tmin= 15;
    Hmax=70;
    Hmin=60;
    twmax = 18;
    gazmax =300;
    }
    break;
 case 3:

    if(data.dey_feeding<=14)
   { Tmax=29;
    Tmin= 25;
    Hmax=85;
    Hmin=55;
    twmax = 25;
    gazmax =300;
     //повне освітлення (24 години на добу)
   }
   else
   { Tmax=18;
    Tmin= 14;
    Hmax=80;
    Hmin=70;
    twmax = 16;
    gazmax =300;
    }
     break;
  case 4:// параметри утримання перепілки
  
     if(data.dey_feeding<=14)
    {Tmax=38;
    Tmin=30;
    Hmax=75;
    Hmin=45;
    twmax = 25;
    gazmax =300;
    
   } 
    else
   { Tmax=25;
    Tmin= 19;
    Hmax=70;
    Hmin=55;
    twmax = 21;
    gazmax =300;
    }
    break;
 
  case 5:
 
   if(data.dey_feeding<=14)
   {Tmax=27;
    Tmin=16;
    Hmax=75;
    Hmin=45;
    twmax = 25;
    
    gazmax =300;
   }
  else
   { Tmax=23;
    Tmin= 19;
    Hmax=70;
    Hmin=55;
    twmax = 18;
    gazmax =300;
    }
    break;
  case 6:
 
   if(data.dey_feeding<=14)
   {Tmax=27;
    Tmin=16;
    Hmax=75;
    Hmin=45;
    twmax = 25;
    gazmax =300;
   
    }
      else
   { Tmax=20;
    Tmin= 16;
    Hmax=70;
    Hmin=65;
    twmax = 18;
    gazmax =550;
    }
     break;
    case 7:
 
   if(data.dey_feeding<=14)
   {Tmax=23;
    Tmin=20;
    Hmax=80;
    Hmin=70;
    twmax = 20;
    gazmax =300;
    }
      else
   { Tmax=18;
    Tmin= 14;
    Hmax=80;
    Hmin=70;
    twmax = 18;
    gazmax =300;
    }
    break;
case 8:
 
   if(data.dey_feeding<=7)
   {Tmax=32;
    Tmin=30;
    Hmax=60;
    Hmin=55;
    twmax = 25;
    gazmax =300;
    }
 else if(data.dey_feeding<=10)
   {Tmax=30;
    Tmin=28;
    Hmax=60;
    Hmin=55;
    twmax = 24;
    gazmax =300;
    }
    else if(data.dey_feeding<=20)
   {Tmax=28;
    Tmin=26;
    Hmax=65;
    Hmin=55;
    twmax = 22;
    gazmax =300;
   }
  else if(data.dey_feeding<=30)
   {Tmax=26;
    Tmin=24;
    Hmax=65;
    Hmin=56;
    twmax = 22;
    gazmax =500;
    } 
  else if(data.dey_feeding<=40)
   {Tmax=24;
    Tmin=22;
    Hmax=65;
    Hmin=55;
    twmax = 20;
    gazmax =300;
   }
      else
   { Tmax=20;
    Tmin= 17;
    Hmax=70;
    Hmin=55;
    twmax = 18;
     gazmax =300;
    }
    break;
    

  }
if (data.routine_feeding==9)
 {  Serial.println(myText[41]);
    Tmax= EEPROM.get(9,Tmax);    // читаємо з пам'яті режим утримання
    
    Tmin= EEPROM.get(7,Tmin);    // читаємо з пам'яті режим утримання
   
    Hmax=EEPROM.get(13,Hmax);    // читаємо з пам'яті режим утримання
   
    Hmin=EEPROM.get(11,Hmin);    // читаємо з пам'яті режим утримання
    
    twmax = EEPROM.get(15,twmax);    // читаємо з пам'яті режим утримання
   
   }

//Serial.print(myText[54]);Serial.print(Tmax);Serial.print(myText[32]);
//Serial.print(myText[55]);Serial.print(Tmin);Serial.println(myText[32]);
//Serial.print(myText[56]);Serial.print(Hmax);Serial.print(myText[26]);
//Serial.print(myText[57]);Serial.print(Hmin);Serial.println(myText[26]);
//Serial.print(myText[58]);Serial.print(twmax);Serial.println(myText[32]);
//Serial.print(myText[59]);Serial.println(gazmax);//Serial.println(F("ppm;"));
//Serial.println();


   
 }
}