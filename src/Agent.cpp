/**
 * @file Agent.cpp
 * @brief Fichier de définition des méthodes de la classe Agent.
 */

#include "Agent.hpp"

/**
 * @fn Agent::Agent(int x, int y, EQUIPE)
 * @brief Constructeur de Agent.
 * @param int x - *Position x d'instantiation de l'agent*
 * @param int y - *Position y d'instantiation de l'agent*
 * @param EQUIPE equipe - *Nom de l'équipe de l'agent*
 */
Agent::Agent(int x, int y, EQUIPE equipe)
    : _position(x, y), _level(1), _memoire(equipe) {}

/**
 * @overload Agent::Agent(Point position, EQUIPE equipe)
 * @param Point position - *Position d'instanciation de l'agent*
 * @param EQUIPE equipe - *Nom de l'équipe de l'agent*
 */
Agent::Agent(Point position, EQUIPE equipe)
    : _position(position), _level(1), _memoire(equipe) {}

/**
 * @fn void Agent::deplacer(Direction dir)
 * @brief Deplace l'agent suivant une direction.
 * @param DIRECTION dir - *Direction de déplacement*
 */
void Agent::deplacer(DIRECTION direction)
{
    // Ne vérifie pas s'il peut se déplacer

    Point pointDir = directionToPoint(direction);

    _position = _position + pointDir;

    // switch (direction)
    // {
    // case DIRECTION::NORDOUEST:
    //     deplacerNordOuest();
    //     break;
    // case DIRECTION::OUEST:
    //     deplacerOuest();
    //     break;
    // case DIRECTION::SUDOUEST:
    //     deplacerSudOuest();
    //     break;
    // case DIRECTION::SUDEST:
    //     deplacerSudEst();
    //     break;
    // case DIRECTION::EST:
    //     deplacerEst();
    //     break;
    // case DIRECTION::NORDEST:
    //     deplacerNordEst();
    //     break;
    // default:
    //     std::cerr << "Direction non reconnue : " << endl;
    //     break;
    // }
}

/*
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
*/

/**
 * @fn void Agent::partagerMemoireAuVoisinage(Agent *voisinage[6])
 * @brief Partage la mémoire aux copains adjacents.
 * 
 * @param Agent * voisinage[6] - *Tableau contenant les agents adjacents*
 * 
 * @details
 * Parcours tous ses voisins et partage sa mémoire avec les agents 
 * de la même équipe.
 */
void Agent::partagerMemoireAuVoisinage(Agent *voisinage[6])
{
    EQUIPE equipeAgent = this->_memoire.getEquipe();

    // Pour chaque cases voisines
    for (int i = 0; i < 6; ++i)
    {
        if (voisinage[i] != nullptr &&
            voisinage[i]->_memoire.getEquipe() == equipeAgent)
        { // Il y a bien un voisin et c'est un copain
            this->partagerMemoireACopain(voisinage[i]);
        }
    }
}

/**
 * @fn void Agent::partagerMemoireACopain(Agent * copainAdjacent)
 * @brief Partage sa mémoire à son copain.
 * 
 * @param Agent * copainAdjacent - *Agent adjacent de la même équipe*
 *  
 * @warning Il peut ne pas y avoir d'agent adjacent => nullptr.
 */
void Agent::partagerMemoireACopain(Agent *copainAdjacent)
{
    if (copainAdjacent != nullptr)
    { // Transmet mémoire qui est acquise par l'agent adjacent
        copainAdjacent->aquerirMemoire(this->_level, this->_memoire);
    }
    else
    {
        cerr << "Je suis triste j'ai pas de copains à proximités" << endl;
    }
}

/**
 * @fn void Agent::aquerirMemoire(int levelAgentTransmetteur, Memoire &memoire)
 * @brief Apprend en fonction du level de l'agent transmetteur de mémoire.
 * 
 * @param int levelAgentTransmetteur - *Level de l'agent qui transmet sa mémoire*
 * @param const Memoire &memoire - *Memoire de l'agent qui transmet sa mémoire*
 *
 *  @details
 * Apprend de la mémoire d'un autre agent.
 * L'influence de l'agent transmetteur dépend de sa différence 
 * de level par rapport à l'agent qui reçoit la mémoire.
 */
void Agent::aquerirMemoire(int levelAgentTransmetteur, const Memoire &memoire)
{
    int diffLevel = (levelAgentTransmetteur - this->_level);

    float influence = this->_memoire.getInfluence(diffLevel);

    this->_memoire.apprentissage(influence, memoire);
}
