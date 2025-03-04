#include "Moyenne.h"
#include <math.h>

// Calcul de la moyenne glissante sur N valeurs
float calcul_moyenne_glissante(float new_temperature)
{
    const int N = 10;  
    float temperature_buffer[N] = {0};
    bool temperature_initialisation = false;
    int buffer_index = 0; 

    // Initialisation du buffer avec la première valeur
    if (temperature_initialisation == false)
    {
        for (int i = 0; i < N;i++)
        {
            temperature_buffer[i] = new_temperature;
        }
        temperature_initialisation = true;
    }

    // Mise à jour du buffer circulaire
    temperature_buffer[buffer_index] = new_temperature;
    buffer_index = (buffer_index + 1) % N;

    // Calcul de la moyenne
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += temperature_buffer[i];
    }

    return sum / N;
}

// Calcul de l'écart type sur les N dernières valeurs
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