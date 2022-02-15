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
        //Getters et setters
        void setCase(int i, int j, EQUIPE equipe);
        Agent * getAgent(int i, int j) const;
        void setAgent(int i, int j, Agent * agent);

        //Méthodes sur la manipulation des données
        void afficherCarte() const;
        bool estVide(int i, int j) const;
        void casesAdjacentes(Agent * agent, EQUIPE voisinage[6]) const;
        void agentsAdjacents(Agent * agent, Agent * voisinage[6]) const;
        void deplacerAgent(Agent * agent, Point origine, Point Destination);
        void deplacerAgent(Agent * agent, Point Destination);
<<<<<<< HEAD
        void correctionPositionAgent(Agent *agent);
=======
>>>>>>> main
};

#endif