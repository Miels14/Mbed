#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include "LED.h"

float calcul_moyenne_glissante(float new_temperature);
float calcul_ecart_type(int new_buffer_index,float new_temperature_buffer[],float new_temperature);

UnbufferedSerial Teraterm(USBTX, USBRX, 115200);
AnalogIn adc_temperature(PA_3);
//AnalogOut dac(PC_0);

Ticker mytick;
float adc_value = 0, voltage = 0, temperature = 0, ecart_type_value = 0;
float val_sin = 0;
char temperature_buffer_value[200],ecart_type_buffer_value[200];
const int N = 10;  
float temperature_buffer[N] = {0}; 
int buffer_index = 0; 


// main() runs in its own thread in the OS
int main()
{
    Teraterm.format(8, SerialBase::None, 1);

    mytick.attach([]()
    {
       /* sprintf(temperature_buffer_value, "$%4.2f;", temperature); 
        Teraterm.write(temperature_value, strlen(temperature_value));*/
        sprintf(temperature_buffer_value, "Valeur de la temperature = %3.2f\n", temperature); 
        Teraterm.write(temperature_buffer_value, strlen(temperature_buffer_value));
        sprintf(ecart_type_buffer_value, "Valeur de l'écart type = %4.2f\n",ecart_type_value);
        Teraterm.write(ecart_type_buffer_value,strlen(ecart_type_buffer_value));

    }, 100ms);

    while (true)
    {
        adc_value = adc_temperature.read();
        voltage = adc_value * 3.3;
        temperature = voltage * 100; 
        temperature = calcul_moyenne_glissante(temperature);
        ecart_type_value = calcul_ecart_type(N, temperature_buffer,temperature);
        Led_affichage(temperature);
       /* for (int i = 0; i < N; i++) 
        {   
        char buffer_msg[50];
        sprintf(buffer_msg, "temperature_buffer[%d] = %4.2f\n", i, temperature_buffer[i]);
        Teraterm.write(buffer_msg, strlen(buffer_msg));
        }*/
     /*   for (int i = 0; i < 10; i++) 
        {
            val_sin = sinf(2.0*3.14*i);
            dac.write(val_sin);
        }*/
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

float calcul_ecart_type(int new_buffer_index,float new_temperature_buffer[],float new_temperature)
{
    float ecart_type = 0;
    for (int i = 0; i < new_buffer_index; i++) 
    {
        ecart_type = ecart_type + powf((new_temperature_buffer[i]-new_temperature),2);
    }
    ecart_type = sqrtf(ecart_type/new_buffer_index);

    return ecart_type;
}

