#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>

UnbufferedSerial Teraterm(USBTX, USBRX, 9600);
AnalogIn adc_temperature(PA_3);


// main() runs in its own thread in the OS
int main() 
{
    float adc_value = 0, voltage = 0, temperature = 0;
    char temperature_value[200];

    Teraterm.write("Connexion a TeraTerm\r",21);
   while (true)
   {
       
       adc_value = adc_temperature.read();
       voltage = adc_value * 3.3;
       temperature = voltage * 100;
       if (Teraterm.writeable()==1) 
       {
           sprintf(temperature_value,"La valeur de la temperature est = %.2fC et la valeur de la tension est = %.3fV et la valeur de l'adc %.3f\n"
           , temperature,voltage,adc_value);
           Teraterm.write(temperature_value, strlen(temperature_value));
       }


        ThisThread::sleep_for(1000ms);
   }
}