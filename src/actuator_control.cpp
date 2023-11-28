// Функція підключення актуатора до Arduino
//const int extendPin = 15;  // Пін для висування штоку актуатора


#include "main.h" // підключаємо головний файл з назвами функцій

const int retractPin = 16;  // Пін для засування штоку актуатора

// Часові інтервали
const unsigned long intervalOn = 2UL * 60UL * 1000UL;  // Інтервал увімкнення актуатора (2 хвилини)
const unsigned long intervalOff = 90UL * 60UL * 1000UL;  // Інтервал вимкнення актуатора (90 хвилин)

unsigned long previousMillis = 0;  // Зберігає час останнього включення актуатора

// Стан актуатора
enum ActuatorState {
  RETRACTED,  // Шток засунутий
  EXTENDED    // Шток висунутий
};

ActuatorState currentState = RETRACTED;  // Початковий стан актуатора

int timer_actuator = 2;  // Час включення актуатора (у хвилинах)

void setup() {
  pinMode(extendPin, OUTPUT);
  pinMode(retractPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Перевірка, чи настав час увімкнення актуатора
  if (currentMillis - previousMillis >= (currentState == EXTENDED ? intervalOff : intervalOn)) {
    previousMillis = currentMillis;

    // Зміна стану актуатора
    if (currentState == RETRACTED) {
      extendActuator();  // Висунути шток
      currentState = EXTENDED;
    } else {
      retractActuator();  // Засунути шток
      currentState = RETRACTED;
    }
  }
}

// Висунення штоку актуатора
void extendActuator() {
  digitalWrite(extendPin, HIGH);  // Встановлення піну для висування штоку актуатора в HIGH
  digitalWrite(retractPin, LOW);  // Встановлення піну для засування штоку актуатора в LOW

  delay(timer_actuator * 60 * 1000);  // Затримка на вказаний час в хвилинах

  digitalWrite(extendPin, LOW);  // Встановлення піну для висування штоку актуатора в LOW
}

// Засування штоку актуатора
void retractActuator() {
  digitalWrite(extendPin, LOW);  // Встановлення піну для висування штоку актуатора в LOW
  digitalWrite(retractPin, HIGH);  // Встановлення піну для засування штоку актуатора в HIGH

  delay(timer_actuator * 60 * 1000);  // Затримка на вказаний час в хвилинах

  digitalWrite(retractPin, LOW);  // Встановлення піну для засування штоку актуатора в LOW
}