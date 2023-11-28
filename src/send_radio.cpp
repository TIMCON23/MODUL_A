/*
 *функція відправки структур даних і тривожних повідомлень
 *в системі TIMCON
 *
 *NRF24L01
 *- створюємо у кожному передавачі структуру даних
 *- створюємо у кожному передавачі String - тривожні повідомлення
 *- створюємо такод масив даних з портів 
 *
 *готуємо відправку
 *циклічно - через кожних 5 хвилин 
 *відправляємо структуру, якщо запущено роботу модуля в 
 *робочому режимі
 *
 *- у разі винекнення помилок чи проблем - 
 *відправляємо тривожні повідомлення 
 *
 *отримуємо у зворотньому пакеті команди у вигляді шифрованих чисел
 *
 * 
 * 
 * 
 */
#pragma once
#include "main.h" // підключаємо головний файл з назвами функцій

void send_radio(){

  if (millis() % (5 * 60 * 1000) == 0) {
    // Отримуємо дані для передачі (наприклад, з датчиків або інших джерел)
    incubator_1.routing1 = 1;
    incubator_1.number1 = 5;
    incubator_1.dey1 = 10;
    incubator_1.t1 = 37.5;
    incubator_1.h1 = 60;
    incubator_1.tegg1 = 37.2;
    incubator_1.CO2 = 500;

    // Відправляємо дані через модуль NRF24L01
    radio.write(&incubator_1, sizeof(incubator_1));

    Serial.println("Дані відправлено");
  }

  // Передавати тривожні повідомлення за потреби
  if (flag_Clock) {
    String warningMessage = "Warning! CLock!";

    // Відправляємо тривожне повідомлення через модуль NRF24L01
    radio.write(warningMessage.c_str(), warningMessage.length() + 1);

    Serial.println("Тривожне повідомлення відправлено");
  }

if (flag_power) {
    String warningMessage = "Warning! POWER!";

    // Відправляємо тривожне повідомлення через модуль NRF24L01
    radio.write(warningMessage.c_str(), warningMessage.length() + 1);

    Serial.println("Тривожне повідомлення відправлено");
  }

if (flag_sensor_Si7021) {
    String warningMessage = "Warning! Sensor_Si7021!";

    // Відправляємо тривожне повідомлення через модуль NRF24L01
    radio.write(warningMessage.c_str(), warningMessage.length() + 1);

    Serial.println("Тривожне повідомлення відправлено");
  }

}