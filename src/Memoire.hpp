/**
 * @file Memoire.hpp
 * @brief Fichier entête de la classe Memoire.
 */
#ifndef MEMOIRE_HPP
#define MEMOIRE_HPP

#include <iostream>

/**
 * @class Memoire
 * @brief Classe contenant la Memoire d'un Agent.
 */
class Memoire
{

private:
    const float _tailleMemoire = 1.;
    float _division;
    float _deplacement;
    float _renforcement;

public:
    Memoire();
    Memoire(float division, float depalcement, float renforcement);
    // Getter
    float getDivision() const { return _division; }
    float getDeplacement() const { return _deplacement; }
    float getRenforcement() const { return _renforcement; }

    // Setter
    void setDivision(float valeur) { _division = valeur; }
    void setDeplacement(float valeur) { _deplacement = valeur; }
    void setRenforcement(float valeur) { _renforcement = valeur; }

    void apprentissage(float influence, const Memoire &memoire);

private:
    void correctionMemoire();
};

#endif