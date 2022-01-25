#ifndef CARTE_HPP
#define CARTE_HPP

#include "Agent.hpp"
#include "Direction.hpp"

const int TAILLE = 10;

class Carte
{
    int _grille[TAILLE][TAILLE];
    Agent * _grilleAgents[TAILLE][TAILLE];

    public:
        Carte();
        void afficherCarte() const;
        void changerCase(int i, int j, int val);
        Agent * getAgent(int i, int j);
        void setAgent(int i, int j, Agent * agent);
        bool estVide(int i, int j);
        //void deplacerAgent(Agent * agent, Direction dir);
};

#endif