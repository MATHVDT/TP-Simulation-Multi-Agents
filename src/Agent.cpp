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
    : _position(x, y), _level(1), _memoire(equipe),
      _action(ACTION::INACTIF) {}

/**
 * @overload Agent::Agent(Point position, EQUIPE equipe)
 * @param Point position - *Position d'instanciation de l'agent*
 * @param EQUIPE equipe - *Nom de l'équipe de l'agent*
 */
Agent::Agent(Point position, EQUIPE equipe)
    : _position(position), _level(1), _memoire(equipe),
      _action(ACTION::INACTIF) {}

/**
 * @fn void Agent::deplacer(Direction dir)
 * @brief Deplace l'agent suivant une direction.
 * @param DIRECTION dir - *Direction de déplacement*
 * 
 * @warning Ne vérifie pas s'il sort de la map, 
 * et s'il y a de la place.
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

/**
 * @fn Point Agent::agir(Agent *voisinage[6])
 * @brief Action de l'agent dans le tour.
 * 
 * @param Agent *voisinage[6] - *Voisinage de l'agent*
 */
Point Agent::agir(Agent *voisinage[6])
{
    // Level general des equipes
    int levelEnnemis = 0;
    int levelAmis = this->_level;

    // Nombre de directions potentielles de deplacement
    int nbDirPossible = 0;
    bool direction[6];

    // Check le voisinage
    for (int i = 0; i < 6; ++i)
    {
        if (voisinage[i] == nullptr)
        {
            direction[i] = true; // Direction de deplacement possible
            ++nbDirPossible;     // Comptage du nb de dir. possibles
        }
        else
        {                         // Agent à proximité
            direction[i] = false; // Pas de proba d'aller dans cette dir.

            if (voisinage[i]->getEquipe() != this->getEquipe())
            { // Ennemi
                levelEnnemis += voisinage[i]->getLevel();
                this->_action = ACTION::ESTATTAQUE;
            }
            else if (voisinage[i]->getEquipe() == this->getEquipe())
            { // Ami
                levelAmis += voisinage[i]->getLevel();
            }
        }
    }

    if (this->_action == ACTION::ESTATTAQUE)
    {
        // ATTAQUE En fct des levels
    }
    else
    {
        // gestion du reste des actions
    }
}
