#include "mbed.h"

UnbufferedSerial Teraterm(USBTX,USBRX,9600); //

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        Teraterm.write("Hello World\n", 12);
        ThisThread::sleep_for(1000ms);
    }
}

