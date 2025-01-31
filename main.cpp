#include "mbed.h"

// Initialisation du port série sans buffer (9600 bauds)
UnbufferedSerial Teraterm(USBTX,USBRX,9600); 

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        Teraterm.write("Hello World\n", 12); // Envoi du message sur le port série
        ThisThread::sleep_for(1000ms);// Pause de 1 seconde
    }
}

