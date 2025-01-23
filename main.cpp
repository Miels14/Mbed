#include "mbed.h"
#include "stdlib.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
// main() runs in its own thread in the OS

UnbufferedSerial Teraterm(USBTX,USBRX,9600);
AnalogIn LM35(A0);
EventFlags Flags;

int main() {
    float val_temp = 0,temperature=0;
    bool C = true;
    char val_temperature[200];
    char touche;
    while (true) {

        val_temp = LM35.read()*3.3;
        temperature = val_temp * 100;
        if(Teraterm.writeable()==1 && C == true)
        {
            sprintf(val_temperature, "La valeur de la temperature est = %f °C",temperature);
            Teraterm.write(val_temperature,strlen(val_temperature));
        }
        else if(Teraterm.writeable()==1 && C == false)
        {
            temperature = val_temp*9/5 + 32;
            sprintf(val_temperature, "La valeur de la temperature est = %f °F",temperature);
            Teraterm.write(val_temperature,strlen(val_temperature));
        }

        if(Teraterm.readable()==1)
        {
            Teraterm.read(&touche,1);
            if(touche =='k')
            {
                C = false;
            }
            else if(touche =='c')
            {
                C = true;
            }
        }


        ThisThread::sleep_for(500ms);
    }
    return 0;
}
