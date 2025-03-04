#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include "LED.h"
#include "Moyenne.h"

// Initialisation du port série (115200 bauds)
UnbufferedSerial Teraterm(USBTX, USBRX, 115200);
AnalogIn adc_temperature_1(PA_3);
AnalogIn adc_temperature_2(PC_0);

// Capteur de température (entrée analogique)
Ticker mytick;
float adc_value_1 = 0, voltage_1 = 0, temperature_1 = 0, ecart_type_value_1 = 0;
float adc_value_2 = 0, voltage_2 = 0, temperature_2 = 0, ecart_type_value_2 = 0;
char temperature_buffer_value_1[200],ecart_type_buffer_value_1[200];
char temperature_buffer_value_2[200],ecart_type_buffer_value_2[200];
const int N = 10;  
float temperature_buffer_1[N] = {0}, temperature_buffer_2[N] = {0}; 
int buffer_index = 0; 

// main() runs in its own thread in the OS
int main()
{
    // Configuration du port série
    Teraterm.format(8, SerialBase::None, 1);

    // Timer pour afficher la température et l'écart type toutes les 100 ms
    mytick.attach([]() 
    {
        // Ecriture sur le teraterm la valeur capteur 1 : 
        sprintf(temperature_buffer_value_1, "Valeur de la temperature ° 1 = %3.2f\n", temperature_1); 
        Teraterm.write(temperature_buffer_value_1, strlen(temperature_buffer_value_1));
       // sprintf(ecart_type_buffer_value_1, "Valeur de l'écart type ° 1 = %4.2f\n",ecart_type_value_1);
       // Teraterm.write(ecart_type_buffer_value_1,strlen(ecart_type_buffer_value_1));


        // Ecriture sur le teraterm la valeur capteur 2 : 
        sprintf(temperature_buffer_value_2, "Valeur de la temperature ° 2 = %3.2f\n", temperature_2); 
        Teraterm.write(temperature_buffer_value_2, strlen(temperature_buffer_value_2));
        //sprintf(ecart_type_buffer_value_2, "Valeur de l'écart type ° 2 = %4.2f\n",ecart_type_value_2);
        //Teraterm.write(ecart_type_buffer_value_2,strlen(ecart_type_buffer_value_2));

    }, 1000ms);

    while (true)
    {
        // Lecture du capteur 1 et 2 (valeur entre 0 et 1)
        adc_value_1 = adc_temperature_1.read();
        adc_value_2 = adc_temperature_2.read();
        // Conversion en tension (0 à 3.3V)
        voltage_1 = adc_value_1 * 3.3;
        voltage_2 = adc_value_2 * 3.3;
        // Conversion en °C (ex : 0.2V → 20°C)
        temperature_1 = voltage_1 * 100;
        temperature_2 = voltage_2 * 100; 
        temperature_1 = calcul_moyenne_glissante(temperature_1);
        temperature_2 = calcul_moyenne_glissante(temperature_2);
        ecart_type_value_1 = calcul_ecart_type(N, temperature_buffer_1,temperature_1);
        ecart_type_value_2 = calcul_ecart_type(N,temperature_buffer_2,temperature_2);
        // Mise à jour des LEDs selon la température
        Led_affichage(temperature_1);
    }
  
}

