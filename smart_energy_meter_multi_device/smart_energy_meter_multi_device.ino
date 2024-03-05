#include <EEPROM.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "  " 
#define BLYNK_TEMPLATE_NAME "  "
#include "EmonLib.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const int numDevices = 2; // Number of devices to monitor

EnergyMonitor emon[numDevices];

#define vCalibration1 83.3
#define currCalibration1 0.50

#define vCalibration2 90.0 // Adjust these calibration values for the second device
#define currCalibration2 0.48 // Adjust these calibration values for the second device

BlynkTimer timer;

char auth[] = "  ";
char ssid[] = "  ";
char pass[] = "  ";

float kWh[numDevices] = {0};
int kwh;
unsigned long lastmillis[numDevices];
int billAmount[numDevices] = {0};

// Constants
#define COST_PER_UNIT 0.15  


void myTimerEvent()
{
  for (int i = 0; i < numDevices; i++)
  {
    emon[i].calcVI(20, 2000);
    kWh[i] = kWh[i] + emon[i].apparentPower * (millis() - lastmillis[i]) / 3600000000.0;
    yield();
    Serial.print("\nDevice ");
    Serial.print(i + 1);

    Serial.print(" - Vrms: ");
    Serial.print(emon[i].Vrms, 2);
    Serial.print("V");

    Serial.print("\tIrms: ");   
    Serial.print(emon[i].Irms, 4);
    Serial.print("A");

    Serial.print("\tPower: ");
    Serial.print(emon[i].apparentPower, 4);
    Serial.print("W");

    Serial.print("\tkWh: ");
    Serial.print(kWh[i], 5);
    Serial.print("kWh");


    billAmount[i] =(kwh * COST_PER_UNIT );
    Serial.print("\tbill :");
    Serial.print(billAmount[i],5);

    lastmillis[i] = millis();

    Blynk.virtualWrite(V0 + (i * 4), emon[i].Vrms);
    Blynk.virtualWrite(V1 + (i * 4), emon[i].Irms);
    Blynk.virtualWrite(V2 + (i * 4), emon[i].apparentPower);
    Blynk.virtualWrite(V3 + (i * 4), kWh[i]);
    Blynk.virtualWrite(V8, String(billAmount[i]));
    Blynk.virtualWrite(V9, String(billAmount[i]));
  }
  Blynk.virtualWrite(V10, "ROOM 1");
  Blynk.virtualWrite(V11, "ROOM 2");
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  float billAmount[numDevices] = {0};
  emon[0].voltage(35 , vCalibration1,1.7 );
  emon[0].current(34 ,currCalibration1 );
  emon[1].voltage(33 , vCalibration2,1.7 );
  emon[1].current(32 , currCalibration2  );
  lastmillis[0] = millis();
  lastmillis[1] = millis();
  

  timer.setInterval(5000L, myTimerEvent);
 
}

void loop()
{
  Blynk.run();
  timer.run();

}