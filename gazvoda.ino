#include "GyverButton.h"

// Пины устройств
#define FLOW_METER_PIN   2  // водомер
#define VALVE_PIN        13 // клапан

volatile bool status_valve = false; // изначальное значение клапана

// Пины кнопок
#define BTN_SIG_4        4
#define BTN_SIG_3        6
#define BTN_SIG_2        8
#define BTN_SIG_1        10

GButton buttons[4] = {GButton(BTN_SIG_4), GButton(BTN_SIG_3), GButton(BTN_SIG_2), GButton(BTN_SIG_1)};

#define ml_in_impulse 2.22 // мл в 1 импульсе датчика
volatile float water = 0;  // количество воды для наливания, мл

#define doza 133.33 // значение 1 дозы в мл
// Ёмкость каждой кнопки в мл
const float button_doses[12] = {
  1 * doza, 1.5 * doza, 2 * doza, 2.5 * doza, 3 * doza, 
  4 * doza, 5 * doza, 6 * doza, 8 * doza, 10 * doza, 
  11 * doza, 12 * doza
};

void setup() {
  pinMode(FLOW_METER_PIN, INPUT); // инициализация пина водомера
  pinMode(VALVE_PIN, OUTPUT); // инициализация пина клапана

  attachInterrupt(0, vodomer, RISING); // прерывание по импульсам водомера

  for (int i = 0; i < 4; i++) {
    buttons[i].setDebounce(50);        // настройка антидребезга
    buttons[i].setTimeout(300);        // настройка таймаута на удержание
    buttons[i].setClickTimeout(600);   // настройка таймаута между кликами
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    buttons[i].tick(); // обязательная функция отработки
  }

  // Комбинации нажатий кнопок для добавления значений воды
  if (buttons[0].isClick() == 0 && buttons[1].isClick() == 0 && buttons[2].isClick() == 0 && buttons[3].isClick() == 1) water += button_doses[0]; 
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 0 && buttons[2].isClick() == 1 && buttons[3].isClick() == 0) water += button_doses[1];
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 0 && buttons[2].isClick() == 1 && buttons[3].isClick() == 1) water += button_doses[2];
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 1 && buttons[2].isClick() == 0 && buttons[3].isClick() == 0) water += button_doses[3];
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 1 && buttons[2].isClick() == 0 && buttons[3].isClick() == 1) water += button_doses[4];
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 1 && buttons[2].isClick() == 1 && buttons[3].isClick() == 0) water += button_doses[5];
  else if (buttons[0].isClick() == 0 && buttons[1].isClick() == 1 && buttons[2].isClick() == 1 && buttons[3].isClick() == 1) water += button_doses[6];
  else if (buttons[0].isClick() == 1 && buttons[1].isClick() == 0 && buttons[2].isClick() == 0 && buttons[3].isClick() == 0) water += button_doses[7];
  else if (buttons[0].isClick() == 1 && buttons[1].isClick() == 0 && buttons[2].isClick() == 0 && buttons[3].isClick() == 1) water += button_doses[8];
  else if (buttons[0].isClick() == 1 && buttons[1].isClick() == 0 && buttons[2].isClick() == 1 && buttons[3].isClick() == 0) water += button_doses[9];
  else if (buttons[0].isClick() == 1 && buttons[1].isClick() == 0 && buttons[2].isClick() == 1 && buttons[3].isClick() == 1) water += button_doses[10];
  else if (buttons[0].isClick() == 1 && buttons[1].isClick() == 1 && buttons[2].isClick() == 0 && buttons[3].isClick() == 0) water += button_doses[11];
     
  // Управление клапаном
  if (water > 0 && !status_valve) {
    status_valve = true;
    digitalWrite(VALVE_PIN, HIGH); // открыть клапан
  } else if (water <= 0 && status_valve) {
    status_valve = false;
    digitalWrite(VALVE_PIN, LOW); // закрыть клапан
  }
}

void vodomer() {
  water -= ml_in_impulse; // каждый импульс уменьшает значение water на ml_in_impulse

  if (water <= 0 && status_valve) {
    status_valve = false;
    digitalWrite(VALVE_PIN, LOW); // закрыть клапан
  }
}
