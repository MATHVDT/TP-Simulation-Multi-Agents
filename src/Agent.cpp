/**
 * @file Agent.cpp
 * @brief Fichier de définition des méthodes de la classe Agent.
 */

#include "Agent.hpp"

/**
 * @fn Agent::Agent(int x, int y)
 * @brief Constructeur de Agent.
 * @param int x - *Position x d'instantiation de l'agent*
 * @param int y - *Position y d'instantiation de l'agent*
 */
Agent::Agent(int x, int y)
    : _x(x), _y(y), _level(1), _memoire() {}

/**
 * @fn void Agent::deplacer(Direction dir)
 * @brief Deplace l'agent suivant une direction.
 * @param DIRECTION dir - *Direction de déplacement*
 */
void Agent::deplacer(DIRECTION direction)
{
    // Ne vérifie pas s'il peut se déplacer

    switch (direction)
    {
    case DIRECTION::NORDOUEST:
        deplacerNordOuest();
        break;
    case DIRECTION::OUEST:
        deplacerOuest();
        break;
    case DIRECTION::SUDOUEST:
        deplacerSudOuest();
        break;
    case DIRECTION::SUDEST:
        deplacerSudEst();
        break;
    case DIRECTION::EST:
        deplacerEst();
        break;
    case DIRECTION::NORDEST:
        deplacerNordEst();
        break;
    default:
        std::cerr << "Direction non reconnue : " << endl;
        break;
    }
}

void Agent::deplacerNordOuest()
{ // ↖
    _y -= 1;
}

void Agent::deplacerOuest()
{ // ←
    _x -= 1;
}

void Agent::deplacerSudOuest()
{ // ↙
    _x -= 1;
    _y += 1;
}

void Agent::deplacerSudEst()
{ // ↘
    _y += 1;
}

void Agent::deplacerEst()
{ // →
    _x += 1;
}

void Agent::deplacerNordEst()
{ // ↗
    _x += 1;
    _y -= 1;
}

/**
 * @fn void Agent::communiquer(Agent * copainAdjacent)
 * @brief Partage sa mémoire à son copain.
 * @param Agent * copainAdjacent - *Agent adjacent de la même équipe* 
 * @warning Il peut ne pas y avoir d'agent adjacent => nullptr.
 */
void Agent::communiquer(Agent *copainAdjacent)
{
    if (copainAdjacent != nullptr)
    {
        //copainAdjacent.aquerirMemoire(level, &memoire)
    }
    else
    {
        cerr << "Je suis triste j'ai pas de copains à proximités" << endl;
    }
}