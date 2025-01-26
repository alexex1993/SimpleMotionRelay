# SimpleMotionRelay
![image](https://github.com/user-attachments/assets/2ed03d89-7673-4008-95e5-9c1c488eb4c5)

## Features
- Light on/off on detect motion
- Working in several cores ESP32

## How to connect components

| ESP32-C3 Board | RCWL-0516 |
| ----------- | ----------- |
| GND   | GND   |
| 5V |  VIN  |
|   D0  | OUT (with pull-up resistor 10kOm) |

Also, you can add capacitor to C-TM contact on RCWL-0516 for regulate the repeat trigger time.


| ESP32-C3 Board | Relay 5V |
| ----------- | ----------- |
| GND   | GND   |
| 5V |  VIN  |
|   D1  | OUT  |
|   5V  | COM  |
