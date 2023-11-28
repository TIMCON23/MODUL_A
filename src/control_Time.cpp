// контроль і перше внесення даних в годинник реального часу
// даніі отримані з wemosd1r2

#include"main.h"
#pragma once


void write_time_ds1307 () {

    Wire.beginTransmission(DS1307_ADDRESS);
   
   Wire.write(0x1);
   Wire.write(decToBcd(minute));
   Wire.write(0x2);
   Wire.write(decToBcd(hour)); 
   Wire.write(0x4);
   Wire.write(decToBcd(dayOfMonth));
   Wire.write(0x5);
   Wire.write(decToBcd(month));
   Wire.write(0x6);
   Wire.write(decToBcd(year));
   Wire.endTransmission();

}