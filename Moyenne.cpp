#include "Moyenne.h"
#include <cstdio>
#include <math.h>
#include <stdio.h>



// Calcul de la moyenne glissante sur N valeurs
float calcul_moyenne_glissante(float new_temperature, const int N, Capteur_Temperature& capteur)
{
    // Initialisation du buffer avec la première valeur
    if (!capteur.initialisation)
    {
        for (int i = 0; i < N; i++) 
        {
            capteur.temperature_buffer[i] = new_temperature;
        }
        capteur.initialisation = true;
    }

    // Mise à jour du buffer circulaire
    capteur.temperature_buffer[capteur.buffer_index] = new_temperature;
    capteur.buffer_index = (capteur.buffer_index + 1) % N;

    // Calcul de la moyenne
    float sum = 0;
    for (int i = 0; i < N; i++) {
        sum += capteur.temperature_buffer[i];
    }

    return sum / N;
}

#include <cmath>  // Pour sqrt et pow

// Calcul de l'écart type sur les N dernières valeurs
float calcul_ecart_type(int N, float temperature_buffer[])
{
    float ecart_type = 0;
    float moyenne = 0;

    // Calcul de la moyenne
    for (int i = 0; i < N; i++) {
        moyenne += temperature_buffer[i];
    }
    moyenne /= N;

    // Calcul de la somme des carrés des différences par rapport à la moyenne
    for (int i = 0; i < N; i++) {
        ecart_type += powf((temperature_buffer[i] - moyenne), 2);
    }

    // Calcul de l'écart type
    ecart_type = sqrtf(ecart_type / N);

    return ecart_type;
}