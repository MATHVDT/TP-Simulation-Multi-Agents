/**
 * @file Memoire.hpp
 * @brief Fichier entête de la classe Memoire.
 */
#ifndef MEMOIRE_HPP
#define MEMOIRE_HPP

#include <iostream>

enum class EQUIPE
{
    BLEU,
    ROUGE,
    NEUTRE
};

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
    EQUIPE _equipe;
    EQUIPE _traceMort; // Couleur de la case quand l'agent meurt
    static const float _epsilon;

public:
    Memoire(EQUIPE equipe);
    Memoire(float division,
            float depalcement,
            float renforcement,
            EQUIPE equipe);
    Memoire(const Memoire &memoire) = default;
    ~Memoire() = default;
    // Getter
    float getDivision() const { return _division; }
    float getDeplacement() const { return _deplacement; }
    float getRenforcement() const { return _renforcement; }
    EQUIPE getEquipe() const { return _equipe; }
    EQUIPE getTraceMort() const { return _traceMort; }

    static float getEpsilon() { return _epsilon; }

    // Setter
    void setDivision(float valeur) { _division = valeur; }
    void setDeplacement(float valeur) { _deplacement = valeur; }
    void setRenforcement(float valeur) { _renforcement = valeur; }
    void setEquipe(EQUIPE equipe) { _equipe = equipe; }

    float getInfluence(int differenceLevel);
    void apprentissage(float influence, const Memoire &memoire);

    // Operator
    Memoire &operator=(const Memoire &memoire);

private:
    void correctionMemoire();
};

bool operator==(const Memoire &m1, const Memoire &m2);
bool operator!=(const Memoire &m1, const Memoire &m2);

#endif