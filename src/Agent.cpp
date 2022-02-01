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
 * @param EQUIPE equipe - *Nom de l'équipe de l'agent*
 */
Agent::Agent(int x, int y, EQUIPE equipe)
    : _x(x), _y(y), _level(1), _memoire(), _equipe(equipe) {}

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

/**
 * @fn void Agent::aquerirMemoire(int levelAgentTransmetteur, Memoire &memoire)
 * @brief Apprend en fonction du level de l'agent transmetteur de mémoire.
 * @param int levelAgentTransmetteur - *Level de l'agent qui transmet sa mémoire*
 * @param const Memoire &memoire - *Memoire de l'agent qui transmet sa mémoire*
 * @details
 * Apprend de la mémoire d'un autre agent.
 * L'influence de l'agent transmetteur dépend de sa différence 
 * de level par rapport à l'agent qui reçoit la mémoire.
 * 
 * Le taux d'influence suit une fonction affine : y = a * x + b
 * Taux d'influence :
 * Agent transmetteur +9 level / agent receveur => influence = 0.9
 * Agent transmetteur -9 level / agent receveur => influence 0.1
 */
void Agent::aquerirMemoire(int levelAgentTransmetteur, const Memoire &memoire)
{
    const float a = (0.9 - 0.4) / 9;
    const float b = 0.5;

    int diffLevel = (levelAgentTransmetteur - this->_level);
    float influence = a * (float)diffLevel + b;
    this->_memoire.apprentissage(influence, memoire);
}
