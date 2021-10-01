# Pedestrian crossing traffic light control system using AVR Register level programming :traffic_light::vertical_traffic_light:

![APM](https://img.shields.io/apm/l/vim-mode) ![GitHub top language](https://img.shields.io/github/languages/top/ashensilva96/AVR_Traffic_light)

This project totally done as a Simulation using Proteus 8 Professional software. Also I used Arduino UNO board plugin for add Virtual arduino bard. As the Microcontroller Atmel ATMega328p 8bit AVR Microcontroller used.

## Fatures 
- Accurate 1Hz delay
- 8 Seven segment displays 
- Two Push buttons

## How it work
When You press push button for corssing. 30 seconds countdown start for vehicles. After this 10s countdown start for Pedestrian

## Used Technologies 
- Timer1 (16 bit timer TCNT1) used as the timer
- As the pre scaler 1024 
- To call interupt Timer1_OVF_vect used
- INT0, INT1 registers used for External interupts

Datasheet of Atmel ATmega328p

https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf



