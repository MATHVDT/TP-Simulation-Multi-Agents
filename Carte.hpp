#ifndef CARTE_HPP
#define CARTE_HPP

class Agent{};

const int TAILLE = 10;

class Carte
{
    int _grille[TAILLE][TAILLE];
    Agent * _grilleAgents[TAILLE][TAILLE];

    public:
        Carte();
        void AfficherCarte() const;
        void ChangerCase(int i, int j, int val);
        Agent * getAgent(int i, int j);
        void setAgent(int i, int j, Agent * agent);
};

#endif