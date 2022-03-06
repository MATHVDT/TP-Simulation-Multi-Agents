#include "Manager.hpp"
#include "exception"

Manager *Manager::_singleton = nullptr;

Manager::Manager()
    : _listAgents{}, _carte{}, _nbAgents(0)
{
}

Manager::~Manager()
{
    deleteAgents();
    _singleton = nullptr;
}

/**
 * @brief Supprime les agents de la liste (libère la mémoire).
 */
void Manager::deleteAgents()
{
    // Suppression des agents dans le tableau
    for (auto a : _listAgents)
    {
        delete a;
    }
    _listAgents.clear();
    _nbAgents = _listAgents.size();
}

/**
 * @brief Récupère ou crée un instance de manager *(singleton)*.
 *
 * @return Manager*
 */
Manager *Manager::getInstance()
{
    // Pas d'instance créée => alors création
    if (Manager::_singleton == nullptr)
        _singleton = new Manager();
    return _singleton;
}

/**
 * @brief Initialise deux agents avec des positions aléatoire et la carte.
 *
 */
void Manager::managerInit()
{
    // Reset de la carte
    _carte.resetMap();
    // Suppression des agents déjà existant
    deleteAgents();

    int xBleu = dice_n(TAILLE) - 1;
    int yBleu = dice_n(TAILLE) - 1;
    int xRouge = dice_n(TAILLE) - 1;
    int yRouge = dice_n(TAILLE) - 1;
    // Pour ne pas mettre les agents sur la même case
    while (xRouge == xBleu)
    {
        xRouge = dice_n(TAILLE) - 1;
    }

    // Crée 2 agents
    Agent *agent0Bleu = new Agent{xBleu,
                                  yBleu,
                                  EQUIPE::BLEU};
    Agent *agent0Rouge = new Agent{xRouge,
                                   yRouge,
                                   EQUIPE::ROUGE};

    if (_nbAgents == 0)
    {
        _listAgents.push_back(agent0Bleu);
        _carte.setAgent(agent0Bleu->getY(),
                        agent0Bleu->getX(),
                        agent0Bleu);
        _carte.setCase(agent0Bleu->getY(),
                       agent0Bleu->getX(),
                       agent0Bleu->getEquipe());

        _listAgents.push_back(agent0Rouge);
        _carte.setAgent(agent0Rouge->getY(),
                        agent0Rouge->getX(),
                        agent0Rouge);
        _carte.setCase(agent0Rouge->getY(),
                       agent0Rouge->getX(),
                       agent0Rouge->getEquipe());

        _nbAgents += 2;
    }
    else
    {
        throw bad_alloc();
    }
}
/**
 * @brief Effecture une simulation.
 *
 * @param int nbTour - *Nombre de tours de simulation*
 */
void Manager::simulation(int nbTour)
{
    cerr << "Simulation pour " << nbTour << " tours." << endl;
    managerInit();
    for (int i = 0; i < nbTour; ++i)
    {
        tour();
    }
}

/**
 * @brief Effecture une simulation avec l'animation dans la console.
 *
 * @param int nbTour - *Nombre de tours de simulation*
 * @param std::chrono::milliseconds frameTpsMs
 */
void Manager::simulationAnimee(int nbTour,
                               std::chrono::milliseconds frameTpsMs)
{
    cerr << "Simulation pour " << nbTour << " tours." << endl;
    managerInit();
    for (int i = 0; i < nbTour; ++i)
    {
        tour();
        afficherCarte();
        std::this_thread::sleep_for(frameTpsMs);
        system("clear");
    }
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
        cerr << "\n\n heho plus d'agent !!!!! \n\n";

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
        agent->correctionPositionAgent();

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

            agentClone->correctionPositionAgent();

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

/**
 * @fn Manager::melangerOrdreAgent
 * @brief Mélange l'ordre des agents de chaque équipe dans leurs vecteurs respectifs.
 */
void Manager::melangerOrdreAgent()
{
    fisherYates(_listAgents);
}

void fisherYates(vector<Agent *> listAgent)
{
    int n = listAgent.size();
    int i;
    int j;

    for (i = n - 1; i > 0; i--)
    {
        // j = rand() % i + 1;
        j = ((dice_n(n) - 1) % i) + 1;

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
        // std::cerr << "Suppression agent mort" << endl;
        // Suppression de l'agent dans la carte
        // ...
        _carte.suppressionAgent(agentCour);

        std::vector<Agent *>::iterator it = _listAgents.begin() + iAgent;

        _listAgents.erase(it);

        --_nbAgents;

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
