/**
 * @file Memoire.cpp
 * @brief Fichier de définition des méthodes de la classe Memoire.
 */

#include "Memoire.hpp"

const float Memoire::_epsilon = 1e-3;

/**
 * @fn Memoire::Memoire()
 * @brief Constructeur de la mémoire.
 *
 * @param EQUIPE equipe - *Equipe de l'agent*
 *
 * @details
 * Initialise des les valeurs _division/_deplacement/_renforcement
 * au même valeur.
 *
 * @warning Les trois valeurs sont à 1./3., somme de la mémoire environ égale à 1 !
 * @todo Faire des opérateurs pour prendre en compte les aproximations des floats
 */
Memoire::Memoire(EQUIPE equipe)
    : _division(1. / 3.),
      _deplacement(1. / 3.),
      _renforcement(1. / 3.),
      _equipe(equipe),
      _traceMort(EQUIPE::NEUTRE) {}

Memoire::Memoire(float division,
                 float depalcement,
                 float renforcement, EQUIPE equipe)
    : _division(division),
      _deplacement(depalcement),
      _renforcement(renforcement),
      _equipe(equipe),
      _traceMort(EQUIPE::NEUTRE)
{
    this->correctionMemoire();
}

/**
 * @fn float Memoire::getInfluence
 * @brief Calcul l'influence de l'agent sur celui-ci.
 *
 * @param int differenceLevel - *Différence de level entre les 2sagents*
 *
 * @details
 * Calcul l'influence de l'agent qui transmet sa mémoire en fonction de la différence de niveau.
 *
 * Le taux d'influence suit une fonction affine : y = a * x + b
 * Taux d'influence :
 * Agent transmetteur +9 level / agent receveur => influence = 0.9
 * Agent transmetteur -9 level / agent receveur => influence 0.1
 */
float Memoire::getInfluence(int differenceLevel)
{
    const float a = (0.9 - 0.4) / 9;
    const float b = 0.5;
    float influence = a * (float)differenceLevel + b;
    return influence;
}

/**
 * @fn void Memoire::apprentissage(float influence, Memoire &memoire)
 * @brief
 *
 * @param float influence - *Influence de la mémoire passé en paramètre*
 * @param const Memoire &memoire - *Mémoire sur laquelle on apprend*
 *
 * @warning correctionMemoire est appelée
 */
void Memoire::apprentissage(float influence, const Memoire &memoire)
{
    float newValeurDivision, newValeurDeplacement, newValeurRenforcement;

    // Calcul des nouvelles valeurs
    newValeurDivision = (1 - influence) * this->_division + influence * memoire.getDivision();
    newValeurDeplacement = (1 - influence) * this->_deplacement + influence * memoire.getDeplacement();
    newValeurRenforcement = (1 - influence) * this->_renforcement + influence * memoire.getRenforcement();

    // Application des nouvelles valeurs
    this->setDivision(newValeurDivision);
    this->setDeplacement(newValeurDeplacement);
    this->setRenforcement(newValeurRenforcement);

    // Appel de la correction
    this->correctionMemoire();
}

/**
 * @fn void Memoire::correctionMemoire()
 * @brief Corrige les valeurs de la mémoire pour avoir une somme environ égale à 1.
 *
 * @details
 * Les calculs des nouvelles valeurs de mémoire (division/deplacement/renforcement)
 * sont effectués et si delta = |1 - somme| < epsilon,
 * alors on essaye de corriger en rajoutant uniformement
 * ce delta au 3 valeurs de mémoire.
 * @warning const float epsilon = 1e-3;
 */
void Memoire::correctionMemoire()
{
    // Recuperation des valeurs
    float valeurDivision = this->getDivision();
    float valeurDeplacement = this->getDeplacement();
    float valeurRenforcement = this->getRenforcement();

    // Calcul de la somme des valeurs
    float somme = valeurDivision + valeurDeplacement + valeurRenforcement;

    // Delta pour Somme =(exact) 1.
    float delta = 1 - somme;

    // Correction s'il y a eu des erreurs sur les arrondis
    if (delta > Memoire::getEpsilon())
    { // Manque un petit peu dans chaque valeur
        valeurDivision += delta / 3.;
        valeurDeplacement += delta / 3.;
        valeurRenforcement += delta / 3.;
        std::cerr << "Correction de +" << delta / 3.;
    }
    else if (delta < -Memoire::getEpsilon())
    {
        valeurDivision -= delta / 3.;
        valeurDeplacement -= delta / 3.;
        valeurRenforcement -= delta / 3.;
        std::cerr << "Correction de -" << delta / 3.;
    }
    else
    {
        return;
    }

    // Application des valeurs corrigées
    this->setDivision(valeurDivision);
    this->setDeplacement(valeurDeplacement);
    this->setRenforcement(valeurRenforcement);
}

Memoire &Memoire::operator=(const Memoire &memoire)
{
    // Guard self assignment
    if (this == &memoire)
        return *this;

    // Copie stat
    this->_division = memoire._division;
    this->_deplacement = memoire._deplacement;
    this->_renforcement = memoire._renforcement;

    // Copie couleur Equipe
    this->_equipe = memoire._equipe;

    return *this;
}

/**
 * @fn operator==(const Memoire &m1, const Memoire &m2)
 * @brief Surcharge de l'opérateur == pour la class Mémoire
 *
 * @param const Memoire &m1
 * @param const Memoire &m2
 * @return true
 * @return bool - *Résultat de l'égalité*
 */
bool operator==(const Memoire &m1, const Memoire &m2)
{
    return (m1.getDivision() == m2.getDivision() &&
            m1.getDeplacement() == m2.getDeplacement() &&
            m1.getRenforcement() == m2.getRenforcement() &&
            m1.getEquipe() == m1.getEquipe() &&
            m1.getTraceMort() == m2.getTraceMort() &&);
}
