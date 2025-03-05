#pragma once

// Structure pour gérer l'initialisation et le buffer pour chaque capteur
struct Capteur_Temperature {
    bool initialisation;
    float * temperature_buffer;
    int buffer_index;
};

// Déclaration des fonctions de calcul
float calcul_moyenne_glissante(float new_temperature, const int N, Capteur_Temperature& capteur);
float calcul_ecart_type(int N, float temperature_buffer[]);

