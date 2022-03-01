#include "Manager.hpp"

Manager::Manager(Agent *agent0Bleu, Agent *agent0Rouge)
    : _listAgents{},
      _carte{},
      _nbAgents(0)
{
    _listAgents.push_back(agent0Bleu);
    _listAgents.push_back(agent0Rouge);
    _nbAgents += 2;

    _carte.setAgent(agent0Bleu->getY(),
                    agent0Bleu->getX(),
                    agent0Bleu);
    _carte.setAgent(agent0Rouge->getY(),
                    agent0Rouge->getX(),
                    agent0Rouge);

    // _carte.setCase(agent0Bleu->getY(),
    //                agent0Bleu->getX(),
    //                agent0Bleu->getEquipe());
    // _carte.setCase(agent0Rouge->getY(),
    //                agent0Rouge->getX(),
    //                agent0Rouge->getEquipe());
}

Manager::~Manager()
{
}

/**
 * @fn Manager::tour
 * @brief Fait agir tous les agents dans un ordre aléatoire.
 */
void Manager::tour()
{
    _nbAgents = (unsigned int)_listAgents.size();
    // std::cerr << "Debut tour ";
    // cerr << "avec nb agents : " << _nbAgents << endl;

    if ((int)_listAgents.size() < 0)
        cerr << "\n\n heho !!!!! \n\n";

    // Indice de parcours des vecteurs des agents
    unsigned int iAgent = 0;

    Agent *agentCour = nullptr;

    // Melanger ordre de passage des agents
    this->melangerOrdreAgent();

    // ACTION de chaque agennt
    while (iAgent < _nbAgents)
    {

        agentCour = _listAgents.at(iAgent);

        // Action d'un agent
        actionAgent(agentCour);

        // Enlever l'agent de la liste s'il est mort
        updateListAgent(agentCour, iAgent);

        // afficherCarte();
        // std::this_thread::sleep_for(50ms);
    }

    iAgent = 0;
    // COMMUNICATION de chaque agennt
    while (iAgent < _nbAgents)
    {

        agentCour = _listAgents.at(iAgent);

        // Action d'un agent
        communicationAgent(agentCour);
        ++iAgent; // Agent suivant
    }
}

/**
 * @fn void Manager::actionAgent
 * @brief Fait agir un agent sur la carte.
 *
 * @param Agent *agent - *Agent qui agit*
 *
 * @details
 * Fait agir un agent sur la carte, en lui fournissant son voisinage.
 * @todo Tient à jour la carte s'il a bougé ou qu'il s'est divisé.
 *
 * @return bool *Agent vivant*
 */
void Manager::actionAgent(Agent *agent)
{

    // Agent cloné s'il y a division
    Agent *agentClone = nullptr;

    // Création voisinage
    Agent *voisinageAgentVoisins[6];
    EQUIPE voisinageAgentCases[6];

    // Récupération du voisinage
    _carte.agentsAdjacents(agent, voisinageAgentVoisins);
    _carte.casesAdjacentes(agent, voisinageAgentCases);

    // Récupère la position de l'agent avant son possible déplacement
    Point pointDepartAgent = agent->getPosition();
    try
    {
        // Action de l'agent et récupe du clone (en cas de division)
        agentClone = agent->agir(voisinageAgentVoisins, voisinageAgentCases);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n\n";
    }

    // Récupération de l'action de l'agent
    ACTION agentAction = agent->getAction();

    // Agent toujours en vie, on le tient à jour dans la carte
    if (agentAction == ACTION::DEPLACEMENT)
    {
        // Correction de la position de l'agent dans la carte (bord de la map)
        _carte.correctionPositionAgent(agent);

        // Nouvelle posistion de l'agent
        Point pointDestinationAgent = agent->getPosition();

        // Mise à des grille de la carte
        bool caseCapture; // Case change de couleur
        caseCapture = _carte.deplacerAgent(agent, pointDepartAgent, pointDestinationAgent);

        agent->consequenceAction(caseCapture);
    }
    else if (agentAction == ACTION::DIVISION)
    {
        if (agentClone != nullptr)
        {
            // Action de l'agent qui sera une DEPLACEMENT
            agentClone->agir(voisinageAgentVoisins, voisinageAgentCases);

            _carte.correctionPositionAgent(agentClone);

            // Ajout de l'agent cloné dans les listes
            _listAgents.push_back(agentClone);

            // Placement dans la carte
            _carte.setAgent(agentClone->getY(),
                            agentClone->getX(),
                            agentClone);

            _carte.setCase(agentClone->getY(),
                           agentClone->getX(),
                           agentClone->getEquipe());
        }
        else
        {
            cerr << "DIVISION sans crée d'agent !!!" << endl;
        }
    }
}

void Manager::afficherCarte()
{
    _carte.afficherCarteBis();
}

void Manager::afficherCarteCarre()
{
    _carte.afficherCarteCarre();
}

/**
 * @fn Manager::melangerOrdreAgent
 * @brief Mélange l'ordre des agents de chaque équipe dans leurs vecteurs respectifs.
 */
void Manager::melangerOrdreAgent()
{
    // fisherYates(_listAgentBleu);
    // fisherYates(_listAgentRouge);
}

void fisherYates(vector<Agent *> listAgent)
{
    int n = listAgent.size();
    int i;
    int j;

    for (i = n; i > 1; i--)
    {
        j = rand() % i + 1;

        swap(listAgent[i], listAgent[j]);
    }
}

// SUpprime l'agent de la car si besoin
void Manager::updateListAgent(Agent *agentCour,
                              unsigned int &iAgent)
{
    // Récupération de l'état de mort de l'agent ou pas
    bool agentMort = (agentCour->getAction() == ACTION::MORT);

    if (agentMort) // Agent mort
    {
        std::cerr << "Suppression agent mort" << endl;
        // Suppression de l'agent dans la carte
        // ...
        _carte.suppressionAgent(agentCour);

        // std::cerr << "arpès suppression carte et " << _carte.getAgent(agentCour->getY(), agentCour->getX())->getLevel() << endl;

        std::cerr << "lvl agent cour : " << agentCour->getLevel() << endl;

        std::vector<Agent *>::iterator it = _listAgents.begin() + iAgent;

        _listAgents.erase(it);

        --_nbAgents;
        std::cerr << "arpès suppression dans vecteur" << endl;

        // delete agentCour ???
        delete agentCour;
    }
    else // Agent pas mort : Trop fort ce gars en faite !!!
    {
        // Incrémentation des indices de parcours
        ++iAgent;
    }
}

void Manager::communicationAgent(Agent *agent)
{
    // Création voisinage
    Agent *voisinageAgentVoisins[6];

    // Récupération du voisinage
    _carte.agentsAdjacents(agent, voisinageAgentVoisins);

    try
    {
        // Communication de l'agent avec son environnement
        agent->partagerMemoireAuVoisinage(voisinageAgentVoisins);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Communication pas effectuée : " << e.what() << "\n\n";
    }
}
