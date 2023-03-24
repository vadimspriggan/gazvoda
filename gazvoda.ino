#include "GyverButton.h"

//определяем пины каждого устройства
#define FLOW_METER_PIN   2 // водомер
#define VALVE_PIN        13 // клапан

volatile bool status_valve = false; // изначальное значение клапана

//пины для определения бинарного кода каждой кнопки
#define BTN_SIG_4        4
#define BTN_SIG_3        6
#define BTN_SIG_2        8
#define BTN_SIG_1        10

GButton sig4(BTN_SIG_4);
GButton sig3(BTN_SIG_3);
GButton sig2(BTN_SIG_2);
GButton sig1(BTN_SIG_1);

#define ml_in_impulse 2.22 // мл в 1 импульсе датчика
volatile float water = 0; // переменная количества воды для наливания, мл

#define doza 133.33 //значение 1 дозы в мл
// ёмкость каждой кнопки в мл
#define button1 1*doza
#define button2 1.5*doza
#define button3 2*doza
#define button4 2.5*doza
#define button5 3*doza
#define button6 4*doza
#define button7 5*doza
#define button8 6*doza
#define button9 8*doza
#define button10 10*doza
#define button11 11*doza
#define button12 12*doza

// флаги кнопок
/*bool status_button1 = false;
bool status_button2 = false;
bool status_button3 = false;
bool status_button4 = false;
bool status_button5 = false;
bool status_button6 = false;
bool status_button7 = false;
bool status_button8 = false;
bool status_button9 = false;
bool status_button10 = false;
bool status_button11 = false;
bool status_button12 = false;
*/

void setup() {
  pinMode(FLOW_METER_PIN, INPUT); //инициализируем пин водомера
  pinMode(VALVE_PIN, OUTPUT); // инициализируем пин клапана
  
  //инициализируем сигнальные пины с подтяжкой к высокому сигналу, тогда кнопки замыкаем к земле
/*pinMode(BTN_SIG_4, INPUT_PULLUP); 
  pinMode(BTN_SIG_3, INPUT_PULLUP);
  pinMode(BTN_SIG_2, INPUT_PULLUP);
  pinMode(BTN_SIG_1, INPUT_PULLUP);
*/
  attachInterrupt(0, vodomer, RISING); //подключаем прерывания, срабатывает при повышении напряжения

  sig4.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  sig4.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  sig4.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)

  sig3.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  sig3.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  sig3.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)

  sig2.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  sig2.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  sig2.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)

  sig1.setDebounce(50);        // настройка антидребезга (по умолчанию 80 мс)
  sig1.setTimeout(300);        // настройка таймаута на удержание (по умолчанию 500 мс)
  sig1.setClickTimeout(600);   // настройка таймаута между кликами (по умолчанию 300 мс)

}

void loop() {
  // обязательная функция отработки. Должна постоянно опрашиваться
  sig4.tick();
  sig3.tick();
  sig2.tick();
  sig1.tick();

  // добавление к переменной water значений воды, соответсвующих каждой из 12 виртуальных кнопок
  if (sig4.isClick() == 0 && sig3.isClick() == 0 && sig2.isClick() == 0 && sig1.isClick() == 1) water =+ button1; 
  else if (sig4.isClick() == 0 && sig3.isClick() == 0 && sig2.isClick() == 1 && sig1.isClick() == 0) water =+ button2;
  else if (sig4.isClick() == 0 && sig3.isClick() == 0 && sig2.isClick() == 1 && sig1.isClick() == 1) water =+ button3;
  else if (sig4.isClick() == 0 && sig3.isClick() == 1 && sig2.isClick() == 0 && sig1.isClick() == 0) water =+ button4;
  else if (sig4.isClick() == 0 && sig3.isClick() == 1 && sig2.isClick() == 0 && sig1.isClick() == 1) water =+ button5;
  else if (sig4.isClick() == 0 && sig3.isClick() == 1 && sig2.isClick() == 1 && sig1.isClick() == 0) water =+ button6;
  else if (sig4.isClick() == 0 && sig3.isClick() == 1 && sig2.isClick() == 1 && sig1.isClick() == 1) water =+ button7;
  else if (sig4.isClick() == 1 && sig3.isClick() == 0 && sig2.isClick() == 0 && sig1.isClick() == 0) water =+ button8;
  else if (sig4.isClick() == 1 && sig3.isClick() == 0 && sig2.isClick() == 0 && sig1.isClick() == 1) water =+ button9;
  else if (sig4.isClick() == 1 && sig3.isClick() == 0 && sig2.isClick() == 1 && sig1.isClick() == 0) water =+ button10;
  else if (sig4.isClick() == 1 && sig3.isClick() == 0 && sig2.isClick() == 1 && sig1.isClick() == 1) water =+ button11;
  else if (sig4.isClick() == 1 && sig3.isClick() == 1 && sig2.isClick() == 0 && sig1.isClick() == 0) water =+ button12;
     
  if (water > 0 ) status_valve = false; else status_valve = true;// открываем клапан пока есть, что наливать, когда будет нечего налить - закрываем

}

void  vodomer() {
// каждый импульc убавляет значение переменной water на ml_in_impulse
 water = water - ml_in_impulse;
 // будет ли прерывание приводить к блокировки основного тела программы? если да, то здесь нужно ещё продублировать проверку переменной water и поставить закрытие клапана
}