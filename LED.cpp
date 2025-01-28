#include "LED.h"

DigitalOut LEDG(PB_0);
DigitalOut LEDB(PB_7);
DigitalOut LEDR(PB_14);

void Led_affichage(float temperature)
 {
    if (temperature >= 25 && temperature < 30)
    {
      LEDG = !LEDG;
      LEDB = 0;
      LEDR = 0;
    }
    else if(temperature >= 30)
    {
        LEDR = !LEDR;
        LEDG = 0;
        LEDB = 0;
    }
    else if(temperature < 25)
    {
        LEDB = !LEDB;
        LEDG = 0;
        LEDR = 0;
    }
    ThisThread::sleep_for(300ms);
}

void Led_On()
{
    LEDR = !LEDR;
    LEDG = !LEDG;
    LEDB = !LEDB;
    ThisThread::sleep_for(300ms);
}

void Led_Off()
{
    LEDR = 0;
    LEDG = 0;
    LEDB = 0;
    ThisThread::sleep_for(300ms);
}