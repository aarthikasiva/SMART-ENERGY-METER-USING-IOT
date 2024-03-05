# SMART-ENERGY-METER-USING-IOT
Energy Monitor and Billing System

This Arduino program monitors the electrical parameters of two devices and calculates the corresponding energy consumption and billing amount. The data is visualized and accessible through the Blynk IoT platform.

Prerequisites:
* Arduino board (tested on ESP32)
* Current and voltage sensors (EmonLib library used)
* Blynk account and project with appropriate widgets

Dependencies:
* EmonLib: Library for energy monitoring
* BlynkSimpleEsp32: Blynk library for ESP32

Blynk Project Setup:
1) Create a new Blynk project.
2) Add the required widgets (Virtual pins V0 to V11).
3) Note down the BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, auth, ssid, and pass.

Hardware Configuration:
1) Connect voltage and current sensors to the specified pins.
2) Adjust calibration values ('vCalibration' and 'currCalibration') for each device.

Installation:
1) Install Arduino IDE and required libraries.
2) Copy and paste the program into your Arduino IDE.
3) Set the correct BLYNK_TEMPLATE_ID, BLYNK_TEMPLATE_NAME, auth, ssid, and pass.
4) Adjust calibration values for each device.
5) Upload the code to your Arduino board.

Operation:
1) The program reads voltage and current from the sensors, calculates power, energy consumption, and billing amount.
2) Data is sent to the Blynk server for real-time monitoring.
3) The system updates every 5 seconds (adjustable with timer.setInterval).

Virtual Pin Mapping:
*  V0: Voltage (Device 1)
*  V1: Current (Device 1)
*  V2: Apparent Power (Device 1)
*  V3: Energy Consumption (Device 1)
*  V8: Billing Amount (Device 1)
*  V9: Billing Amount (Device 2)
*  V10: Room Name (Device 1)
*  V11: Room Name (Device 2)

Notes:

* Adjust calibration values for accurate readings.
* Ensure the Blynk app is configured with the correct project ID, name, and authentication details.
* Modify the billing calculation logic according to your utility rates if necessary.



