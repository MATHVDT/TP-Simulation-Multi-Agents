/**
 * @class class Agent
 * @brief Classe Agent
 */
#ifndef AGENT_HPP
#define AGENT_HPP

#include <iostream>
#include "Direction.hpp"
#include "Memoire.hpp"

using namespace std;

class Agent
{
private:
    int _x;
    int _y;
    int _level;
    Memoire _memoire;

public:
    Agent(int x, int y);

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

    void communiquer(Agent * copainAdjacent);

};

#endif