#include "Agent.hpp"

/**
 * @fn Agent::Agent(int x, int y)
 * @brief Constructeur de Agent.
 * @param int x - *Position x d'instantiation de l'agent*
 * @param int y - *Position y d'instantiation de l'agent*
 */
Agent::Agent(int x, int y) : _x(x), _y(y) {}

void Agent::deplacer(Direction dir)
{
    // Ne vérifie pas s'il peut se déplacer

    switch (dir)
    {
    case NordOuest:
        deplacerNordOuest();
        break;
    case Ouest:
        deplacerOuest();
        break;
    case SudOuest:
        deplacerNordOuest();
        break;
    case SudEst:
        deplacerSudEst();
        break;
    case Est:
        deplacerEst();
        break;
    case NordEst:
        deplacerNordEst();
        break;
    default:
        std::cerr << "Direction non reconnue : " << dir;
        break;
    }
}

void Agent::deplacerNordOuest()
{ // <- et ^
    _y -= 1;
}

void Agent::deplacerOuest()
{ // <-
    _x -= 1;
}

void Agent::deplacerSudOuest()
{
    _y += 1;
}

void Agent::deplacerSudEst()
{
    _x += 1;
    _y += 1;
}

void Agent::deplacerEst()
{
    _x += 1;
}

void Agent::deplacerNordEst()
{
    _x += 1;
    _y -= 1;
}
