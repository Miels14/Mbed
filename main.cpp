#include "mbed.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include "LED.h"
#include "Moyenne.h"

// Initialisation des pins
UnbufferedSerial Teraterm(USBTX, USBRX, 115200);
AnalogIn adc_temperature_1(PA_3);
AnalogIn adc_temperature_2(PC_0);

// Déclaration des variables 
Ticker mytick;
float adc_value_1 = 0, voltage_1 = 0, temperature_1 = 0, ecart_type_value_1 = 0;
float adc_value_2 = 0, voltage_2 = 0, temperature_2 = 0, ecart_type_value_2 = 0;
char temperature_buffer_value_1[200],ecart_type_buffer_value_1[200];
char temperature_buffer_value_2[200],ecart_type_buffer_value_2[200];
const int N = 100;  
Capteur_Temperature capteur_1 = {false,new float[N],0};
Capteur_Temperature capteur_2 = {false,new float[N],0};


// main
int main()
{
    // Configuration du port série
    Teraterm.format(8, SerialBase::None, 1);

    // Ticker
    mytick.attach([]() 
    {
        // Ecriture sur le teraterm la valeur capteur 1 : 
        sprintf(temperature_buffer_value_1, "Valeur de la temperature ° 1 = %3.2f\n", temperature_1); 
        Teraterm.write(temperature_buffer_value_1, strlen(temperature_buffer_value_1));

        // Ecriture sur le teraterm la valeur capteur 2 : 
        sprintf(temperature_buffer_value_2, "Valeur de la temperature ° 2 = %3.2f\n", temperature_2); 
        Teraterm.write(temperature_buffer_value_2, strlen(temperature_buffer_value_2));
    }, 500ms);

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

        // Calcul de la moyenne glissante et mise à jour de l'indice du buffer
        temperature_1 = calcul_moyenne_glissante(temperature_1, N, capteur_1);
        temperature_2 = calcul_moyenne_glissante(temperature_2, N, capteur_2);

        // Calcul de l'écart type
        ecart_type_value_1 = calcul_ecart_type(N, capteur_1.temperature_buffer);
        ecart_type_value_2 = calcul_ecart_type(N, capteur_2.temperature_buffer);

        // Mise à jour des LEDs selon la température
        // Led_affichage(temperature_1);

        ThisThread::sleep_for(100ms);
    }
    // Libérer la mémoire du tableau
    delete [] capteur_1.temperature_buffer;
    delete [] capteur_2.temperature_buffer;
    return 0;
}
