#include "mbed.h"
#include <cstdio>

UnbufferedSerial Teraterm(USBTX,USBRX,9600);
PwmOut led(PA_5);
DigitalIn button(PA_0);


// main() runs in its own thread in the OS
int main()
{
    char Led_value[50];
    float LED = 0;

    while (true) 
    {
        if (button == true) 
        {
            for (float i = 0.0; i <=1.0; i += 0.1)
            {
                led = i;
                LED = led.read();
                ThisThread::sleep_for((500ms));
            }
        }
        if(Teraterm.writable()==1)
        {
            sprintf(Led_value,"La valeur de la led est = %f", LED);
            Teraterm.write(Led_value,strlen(Led_value));
        }
        
        Teraterm.write("Hello World\n", 5);
        ThisThread::sleep_for(1000ms);
    }
}

