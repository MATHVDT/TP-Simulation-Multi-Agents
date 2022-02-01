/**
 * @file Agent.hpp
 * @brief Fichier entête de la classe Agent.
 */
#ifndef AGENT_HPP
#define AGENT_HPP
#include <iostream>
#include "Direction.hpp"
#include "Memoire.hpp"

using namespace std;

enum class EQUIPE
{
    BLEU,
    ROUGE
};

/**
 * @class Agent
 * @brief Classe Agent
 */
class Agent
{
private:
    static const int _levelMax = 10;

private:
    int _x;
    int _y;
    int _level;
    Memoire _memoire;
    EQUIPE _equipe;

public:
    Agent(int x, int y, EQUIPE equipe);

    // Getter
    int getX() const { return _x; }
    int getY() const { return _y; }

    // Setter
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }

    // Deplacement
    void deplacer(DIRECTION dir);

    void deplacerNordOuest();
    void deplacerOuest();
    void deplacerSudOuest();
    void deplacerSudEst();
    void deplacerEst();
    void deplacerNordEst();

    void communiquer(Agent *copainAdjacent);
    void aquerirMemoire(int level, Memoire &memoire);
};

#endif