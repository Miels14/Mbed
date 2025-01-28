#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include "LED.h"

float calcul_moyenne_glissante(float new_temperature);

UnbufferedSerial Teraterm(USBTX, USBRX, 115200);
AnalogIn adc_temperature(PA_3);
Ticker mytick;
float adc_value = 0, voltage = 0, temperature = 0;
char temperature_value[200];
const int N = 10;  
float temperature_buffer[N] = {0}; 
int buffer_index = 0; 

// main() runs in its own thread in the OS
int main()
{
    Teraterm.format(8, SerialBase::None, 1);

    mytick.attach([]()
    {
        sprintf(temperature_value, "$%4.2f;", temperature); 
        Teraterm.write(temperature_value, strlen(temperature_value));  
    }, 200ms);

    while (true)
    {
        adc_value = adc_temperature.read();
        voltage = adc_value * 3.3;
        temperature = voltage * 100; 
        temperature = calcul_moyenne_glissante(temperature);
        Led_affichage(temperature);
        ThisThread::sleep_for(10ms);  
    }
}

float calcul_moyenne_glissante(float new_temperature)
{
    static bool temperature_initialisation = false;

    if (temperature_initialisation == false)
    {
        for (int i = 0; i < N;i++)
        {
            temperature_buffer[i] = new_temperature;
        }
        temperature_initialisation = true;
    }

    temperature_buffer[buffer_index] = new_temperature;
    buffer_index = (buffer_index + 1) % N;
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += temperature_buffer[i];
    }

    return sum / N;
}