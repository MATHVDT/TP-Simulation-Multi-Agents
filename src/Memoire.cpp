/**
 * @file Memoire.cpp
 * @brief Fichier de définition des méthodes de la classe Memoire.
 */

#include "Memoire.hpp"

const float Memoire::_epsilon = 1e-5;

/**
 * @fn Memoire::Memoire
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

/**
 * @overload Memoire::Memoire
 * @brief Construct a new Memoire:: Memoire object
 *
 * @param division
 * @param depalcement
 * @param renforcement
 * @param equipe
 */
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
 * @warning const float epsilon = 1e-5;
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
    return (
        (std::abs(m1.getDivision() - m2.getDivision()) < Memoire::getEpsilon()) &&
        (std::abs(m1.getDeplacement() - m2.getDeplacement()) < Memoire::getEpsilon()) &&
        (std::abs(m1.getRenforcement() - m2.getRenforcement()) < Memoire::getEpsilon()) &&

        (m1.getEquipe() == m2.getEquipe()) &&
        (m1.getTraceMort() == m2.getTraceMort()));
}

/**
 * @fn operator!=(const Memoire &m1, const Memoire &m2)
 * @brief Surcharge de l'opérateur != pour la class Mémoire
 *
 * @param const Memoire &m1
 * @param const Memoire &m2
 * @return true
 * @return bool - *Résultat de l'inégalité*
 */
bool operator!=(const Memoire &m1, const Memoire &m2)
{
    return !(m1 == m2);
}

/**
 * @fn void Memoire::augmenterDeplacement()
 * @brief Augmente la valeur de déplacement.
 *
 * @details
 * Augmente la valeur de déplacement et réduit
 * les valeurs de renforcement et de division
 * par deux. *(Somme doit faire 1)*
 */
void Memoire::augmenterDeplacement()
{
    float valReducRenfo = _renforcement / 2;
    float valReducDiv = _division / 2;

    _deplacement += valReducRenfo + valReducDiv;
    _renforcement -= valReducRenfo;
    _division -= valReducDiv;
}

/**
 * @fn void Memoire::diminuerDeplacement()
 * @brief Diminue la valeur de deplacement
 *
 * @details
 * Divise par deux la valeur de déplacement de la
 * mémoire et augmente équitablement les valeurs de
 * division et renforcement. *(Somme doit faire 1)*
 */
void Memoire::diminuerDeplacement()
{
    float valReduc = _deplacement / 2;

    _deplacement -= valReduc;
    _division += valReduc / 2;
    _renforcement += valReduc / 2;
}
/**
 * @fn void Memoire::diminuerDivision()
 * @brief Diminue la valeur de division.
 *
 * @details
 * Divise par deux la valeur de division
 * et augemente la valeur de renforcement.
 * *(Somme doit faire 1)*
 */
void Memoire::diminuerDivision()
{
    float valReduc = _renforcement / 2;

    _division -= valReduc;
    _renforcement += valReduc;
}
/**
 * @fn void Memoire::augmenterRenforcement()
 * @brief Augmente le renforcement en fonction du level.
 *
 * @param const int ratioLevel - *Level Actuel/Level Max*
 *
 * @details
 * Augmente la valeur du renforcement suivant le
 * niveau actuel et et le niveau max. Reduit la valeur
 * de division. *(Somme doit faire 1)*
 * *[renfo = renfo + (1 - renfo) *( 1 * ratio)]*
 */
void Memoire::augmenterRenforcement(const int ratioLevel)
{
    float valAdd = (1 - _renforcement) * (1 - ratioLevel);

    _renforcement += valAdd;
    _division -= valAdd;
}

/**
 * @fn void Memoire::diminuerRenforcement()
 * @brief Diminue la valeur de renforcement.
 *
 * @details
 * Divise par deux la valeur de renforcement
 * et augmente la valeur de division.
 * *(Somme doit faire 1)*
 */
void Memoire::diminuerRenforcement()
{
    float valReduc = _renforcement / 2;

    _renforcement -= valReduc;
    _division += valReduc;
}