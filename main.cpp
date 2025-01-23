#include "mbed.h"
#include <chrono>
#include <cstdio>

UnbufferedSerial Teraterm(USBTX,USBRX,9600);
PwmOut led(PA_5);
DigitalIn button(PA_0);
DigitalOut buzzer(PA_1);
Timer timer;

// main() runs in its own thread in the OS
int main()
{
    char Led_value[50];
    float LED = 0;
    bool firstpress = false;
    float firstpresstime = 0, durationbetweenpresstime = 0;
    timer.start();
    while (true) 
    {
        if(!firstpress)
        {
            firstpress = true;
            firstpresstime = timer.read_ms();
            timer.reset();

        }
        else
        {
            firstpress = false;
            durationbetweenpresstime = timer.read_ms() - firstpresstime;
            if (durationbetweenpresstime < 500) 
            {
                buzzer = 1;
                ThisThread::sleep_for(200ms);
                buzzer = 0;
                Teraterm.write("Double-clic détecté\n",22);
            }
        }
        ThisThread::sleep_for(1000ms);
    }
}

