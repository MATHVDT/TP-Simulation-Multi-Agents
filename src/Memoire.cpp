/**
 * @file Memoire.cpp
 * @brief Fichier de définition des méthodes de la classe Memoire.
 */

#include "Memoire.hpp"

/**
 * @fn Memoire::Memoire()
 * @brief Constructeur de la mémoire.
 * @details
 * Initialise des les valeurs _division/_deplacement/_renforcement
 * au même valeur.
 * @warning Les trois valeurs sont à 1./3., somme de la mémoire environ égale à 1 !
 * @todo Faire des opérateurs pour prendre en compte les aproximations des floats
 */
Memoire::Memoire()
    : _division(1. / 3.), _deplacement(1. / 3.), _renforcement(1. / 3.) {}


// Memoire::Memoire(float)

/**
 * @fn void Memoire::apprentissage(float influence, Memoire &memoire)
 * @brief
 * @param float influence - *Influence de la mémoire passé en paramètre*
 * @param const Memoire &memoire - *Mémoire sur laquelle on apprend*
 * @warning 
 * Les calculs des nouvelles valeurs de mémoire (division/deplacement/renforcement)
 * sont effectués et si delta = |1 - somme| < epsilon,
 *  alors on essaye de corriger en rajoutant uniformement 
 * ce delta au 3 valeurs de mémoire.
 * const float epsilon = 1e-3; 
 */
void Memoire::apprentissage(float influence,const Memoire &memoire)
{
    const float epsilon = 1e-3;
    float newValeurDivision, newValeurDeplacement, newValeurRenforcement;

    // Calcul des nouvelles valeurs
    newValeurDivision = (1 - influence) * this->_division + influence * memoire.getDivision();
    newValeurDeplacement = (1 - influence) * this->_deplacement + influence * memoire.getDeplacement();
    newValeurRenforcement = (1 - influence) * this->_renforcement + influence * memoire.getRenforcement();

    float somme = newValeurDivision + newValeurDeplacement + newValeurRenforcement;

    float delta = 1 - somme; // Delta pour Somme =(exact) 1.

    // Correction s'il y a eu des erreurs sur les arrondis
    if (delta > epsilon)
    { // Manque un petit peu dans chaque valeur
        newValeurDivision += delta / 3.;
        newValeurDeplacement += delta / 3.;
        newValeurRenforcement += delta / 3.;
        std::cerr << "Correction de +" << delta / 3.;
    }
    else if (delta < -epsilon)
    {
        newValeurDivision -= delta / 3.;
        newValeurDeplacement -= delta / 3.;
        newValeurRenforcement -= delta / 3.;
        std::cerr << "Correction de -" << delta / 3.;
    }

    this->setDivision(newValeurDivision);
    this->setDeplacement(newValeurDeplacement);
    this->setRenforcement(newValeurRenforcement);
}
