/**
 * @class class Agent
 * @brief Classe Agent
 */
#ifndef AGENT_HPP
#define AGENT_HPP

#include <iostream>
#include "Direction.hpp"

class Agent
{
private:
    int _x;
    int _y;

public:
    Agent(int x, int y);

    // Getter
    int getX() const { return _x; }
    int getY() const { return _y; }

    // Setter
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }

    void deplacer(Direction dir);

    void deplacerNordOuest();
    void deplacerOuest();
    void deplacerSudOuest();
    void deplacerSudEst();
    void deplacerEst();
    void deplacerNordEst();
};

#endif