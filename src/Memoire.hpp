/**
 * @file Memoire.hpp
 * @brief Fichier entête de la classe Memoire.
 */
#ifndef MEMOIRE_HPP
#define MEMOIRE_HPP

/**
 * @class Memoire
 * @brief Classe contenant la Memoire d'un Agent.
 */
class Memoire
{

private:
    const float _tailleMemoire = 99;
    float _deplacement;
    float _renforcement;
    float _division;

public:
    Memoire();
    // Getter
    float getDeplacement() { return _deplacement; }
    float getRenforcement() { return _renforcement; }
    float getDivision() { return _division; }

    void apprentissage(float influence, Memoire &memoire);
};

#endif