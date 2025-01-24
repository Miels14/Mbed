#include "mbed.h"

UnbufferedSerial Teraterm(USBTX,USBRX,9600);
EventFlags Flags;

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        Teraterm.write("Hello World\n", 11);
        ThisThread::sleep_for(1000ms);
    }
}

