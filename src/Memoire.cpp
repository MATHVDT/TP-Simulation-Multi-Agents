/**
 * @file Memoire.cpp
 * @brief Fichier de définition des méthodes de la classe Memoire.
 */

#include "Memoire.hpp"

/**
 * @fn Memoire::Memoire()
 * @brief Constructeur de la mémoire.
 * @details
 * Initialise des les valeurs _deplacement/_renforcement/_division
 * au même valeur.
 * @warning Les trois valeurs sont à 1./3., somme de la mémoire environ égale à 1 !
 * @todo Faire des opérateurs pour prendre en compte les aproximations des floats
 */
Memoire::Memoire()
    : _deplacement(1./3.), _renforcement(1./3.), _division(1./3.) {}


void Memoire::apprentissage(float influence, Memoire &memoire)
{

}
