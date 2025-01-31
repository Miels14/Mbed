#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include "LED.h"

UnbufferedSerial Teraterm(USBTX, USBRX,115200);
AnalogIn adc_temperature(PA_3);
Ticker mytick;
float adc_value = 0, voltage = 0, temperature = 0;
 char temperature_value[200];
// main() runs in its own thread in the OS
int main() 
{
    Teraterm.format(8,SerialBase::None,1);
    mytick.attach([]()
    {
        sprintf(temperature_value,"$%4.2f;", temperature);
        Teraterm.write(temperature_value, strlen(temperature_value));
    },20ms);
   while (true)
   {
       adc_value = adc_temperature.read();
       voltage = adc_value * 3.3;
       temperature = voltage * 100; 
       Led_affichage(temperature);
        ThisThread::sleep_for(10ms);
   }
}