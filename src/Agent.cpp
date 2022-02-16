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
Point Agent::agir(Agent *voisinageAgentVoisins[6], EQUIPE voisinageAgentCases[6])
{
    // Level general des equipes
    int levelEnnemis = 0;
    int levelAmis = this->_level;

    // Nombre de directions potentielles de deplacement
    // et info sur le voisinage (level Amis/Ennemis, directonPossible)
    bool direction[6];
    int nbDirPossible = examenVoisinage(voisinageAgentVoisins,
                                        levelEnnemis, levelAmis,
                                        direction);

    // choix action agent
    this->_action = choixAction(levelEnnemis, nbDirPossible);
    // this->_action = ACTION::DEPLACEMENT;

    if (this->_action == ACTION::ESTATTAQUE)
    {
        // ATTAQUE En fct des levels
    }
    else
    {

        if (this->_action == ACTION::DIVISION)
        {
            //
        }
        if (this->_action == ACTION::DEPLACEMENT)
        {
            // Choix direction de déplacement
            DIRECTION directionChoisie = choixDirectionDeplacement(direction);
            deplacer(directionChoisie); // Déplacement de l'agent
        }
        if (this->_action == ACTION::RENFORCEMENT)
        {
            // Gagne un niveau
            ++_level;
        }
        if (this->_action == ACTION::BLOQUE)
        {
            // A le seum et ne fait rien
        }

        if (this->_action == ACTION::INACTIF)
        {
            cout << "Bizarre tu aurais due agir !";
        }
    }

    // Je crois que le retour sert a rien
    return Point{0, 0};
}

/**
 * @fn Agent::choixDirectionDeplacement
 * @brief Choisie une direction de déplacement en fonction des possibilités.
 * 
 * @param bool directionsPossibles[6]
 */
DIRECTION Agent::choixDirectionDeplacement(bool directionsPossibles[6])
{
    int i = rand() % 6;

    DIRECTION directionChoisie = DIRECTION::NULLDIRECTION;

    // Tant que l'on a pas choisie une direction
    while (directionChoisie == DIRECTION::NULLDIRECTION)
    {
        // Si la direction est possible
        if (directionsPossibles[i])
        {                        // La direction est libre
            if (rand() % 6 == 0) // 1 chance sur 6
            {                    // Prendre la direction par rapport au tableau de correspondance
                directionChoisie = intToDirection(i);
            }
        }
    }
    return directionChoisie;
}

/**
 * @overload Agent::operator=
 * @brief Surcharge de l'opérateur d'affectation.
 * 
 * @return Agent &
 */
Agent &Agent::operator=(const Agent &agent)
{
    if (this == &agent) // Guard self assignment
        return *this;

    // Copie position
    this->_position = agent._position;

    // Copie level
    this->_level = agent._level;

    // Copie memoire
    this->_memoire = agent._memoire;

    // Copie action en cours
    this->_action = agent._action;

    return *this;
}

/**
 * @fn Agent::choixAction()
 * @brief Retourne l'action choisie en fonction de la mémoire et environnement.
 * 
 * @param int levelEnnemis - *Somme des levels des ennemis adjacents*
 * @param int nbDirPossible - *Nb directions libres*
 * 
 * @warning 
 * S'il n'a aucune directions libres alors la *DIVISION* et le
 * *DEPLACEMENT* sont *BLOQUE*. 
 * 
 * @return ACTION actionChoisie (DIVISION, DEPLACEMENT, RENFORCEMENT, BLOQUE)
 */
ACTION Agent::choixAction(int levelEnnemis, int nbDirPossible)
{
    double choix = (double)rand() / (double)RAND_MAX; // [0-1]
    ACTION actionChoisie = ACTION::INACTIF;

    if (levelEnnemis > 0) // ie, il ya des ennemis adjacents
    {
        actionChoisie = ACTION::ESTATTAQUE;
    }
    else // Pas d'ennemis adjacents, Tu peux faire ta popote
    {
        if (choix < _memoire.getDivision())
        {                          // Division de l'agent
            if (nbDirPossible > 0) // Il y a de la place pour se diviser
                actionChoisie = ACTION::DIVISION;
            else // Pas de place pour ce diviser
                actionChoisie = ACTION::BLOQUE;
        }
        else if (choix < _memoire.getDivision() + _memoire.getDeplacement())
        {                          // Deplacement de l'agent
            if (nbDirPossible > 0) // Il est possible de se déplacer
                actionChoisie = ACTION::DEPLACEMENT;
            else // Il n'est pas possible de s déplacer
                actionChoisie = ACTION::BLOQUE;
        }
        else // choix restant -> Renforcement
        {    // Renforcement de l'agent
            actionChoisie = ACTION::RENFORCEMENT;
        }
    }

    return actionChoisie;
}

/**
 * @fn Agent::examenVoisinage
 * @brief Analyse le voisinage.
 * 
 * @param  Agent *voisinageAgentVoisins[6]
 * @param int & levelEnnemis
 * @param int & levelAmis
 * @param bool direction[6]
 */
int Agent::examenVoisinage(Agent *voisinageAgentVoisins[6],
                           int &levelEnnemis, int &levelAmis,
                           bool direction[6])
{
    int nbDirPossible = 0;
    // Check le voisinageAgentVoisins
    for (int i = 0; i < 6; ++i)
    {
        if (voisinageAgentVoisins[i] == nullptr) // Pas d'agent sur cette case
        {
            direction[i] = true; // Direction de deplacement possible
            ++nbDirPossible;     // Comptage du nb de dir. possibles
        }
        else
        {                         // Agent à proximité
            direction[i] = false; // Pas de proba d'aller dans cette dir.

            if (voisinageAgentVoisins[i]->getEquipe() != this->getEquipe())
            { // Ennemi : récupération de son level
                levelEnnemis += voisinageAgentVoisins[i]->getLevel();
                this->_action = ACTION::ESTATTAQUE;
            }
            else if (voisinageAgentVoisins[i]->getEquipe() == this->getEquipe())
            { // Ami : récupération de son level
                levelAmis += voisinageAgentVoisins[i]->getLevel();
            }
        }
    }

    return nbDirPossible;
}