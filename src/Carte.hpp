#ifndef CARTE_HPP
#define CARTE_HPP

#include "Agent.hpp"
#include "Direction.hpp"
#include "Point.hpp"
#include "Memoire.hpp"

const int TAILLE = 10;

class Carte
{
    EQUIPE _grille[TAILLE][TAILLE];
    Agent * _grilleAgents[TAILLE][TAILLE];

    public:
        Carte();
        void afficherCarte() const;
        void changerCase(int i, int j, EQUIPE equipe);
        Agent * getAgent(int i, int j) const;
        void setAgent(int i, int j, Agent * agent);
        bool estVide(int i, int j) const;
        void deplacerAgent(Agent * agent, Point origine, Point Destination);
};

#endif