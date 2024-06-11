
# Управление системой налива воды (Water Dispensing System)

Эта программа предназначена для управления системой налива воды с использованием Arduino, водомера и клапана. В зависимости от нажатия кнопок оператором, клапан открывается, наливается нужное количество воды, затем клапан закрывается. Оператор может несколько раз нажать на одну и ту же кнопку, чтобы получить суммарное количество воды.

## Оборудование

- Arduino
- Водомер (подключен к пину 2)
- Клапан (подключен к пину 13)
- Кнопки (подключены к пинам 4, 6, 8 и 10)

## Библиотека

Используется библиотека [GyverButton](https://github.com/AlexGyver/GyverButton), написанная Алекс Гайвером.

## Установка

1. Клонируйте репозиторий или загрузите архив.
2. Установите библиотеку GyverButton через библиотечный менеджер Arduino IDE.
3. Откройте проект в Arduino IDE.
4. Загрузите код на вашу Arduino плату.

## Как использовать

1. Подключите оборудование согласно схемы.
2. Нажмите кнопку для выбора объема воды. Комбинации кнопок соответствуют разным объемам:
   - `0001`: 1 доза
   - `0010`: 1.5 дозы
   - `0011`: 2 дозы
   - и т.д.
3. Клапан откроется и закроется автоматически после достижения нужного объема.

## Лицензия

Этот проект распространяется под лицензией MIT.

---

# Water Dispensing System

This program is designed to control a water dispensing system using Arduino, a flow meter, and a valve. Depending on the operator's button presses, the valve opens, dispenses the required amount of water, and then closes. The operator can press the same button multiple times to get the total amount of water.

## Hardware

- Arduino
- Flow meter (connected to pin 2)
- Valve (connected to pin 13)
- Buttons (connected to pins 4, 6, 8, and 10)

## Library

The [GyverButton](https://github.com/AlexGyver/GyverButton) library by Alex Gyver is used.

## Installation

1. Clone the repository or download the archive.
2. Install the GyverButton library via the Arduino IDE library manager.
3. Open the project in the Arduino IDE.
4. Upload the code to your Arduino board.

## How to Use

1. Connect the hardware according to the schematic.
2. Press a button to select the water volume. Button combinations correspond to different volumes:
   - `0001`: 1 dose
   - `0010`: 1.5 doses
   - `0011`: 2 doses
   - and so on.
3. The valve will open and close automatically after dispensing the required amount.

## License

This project is licensed under the MIT License.
