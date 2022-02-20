#include "Manager.hpp"

Manager::Manager()
    : _listAgentBleu{}, _listAgentRouge{},
      _carte{}
{
}

Manager::~Manager()
{
}

void Manager::managerInit(Agent *agent0bleu, Agent*agent0rouge) {
    _listAgentBleu.push_back(*agent0bleu);
    _carte.setAgent(agent0bleu->getY(), agent0bleu->getX(), agent0bleu);
    _carte.setCase(agent0bleu->getY(), agent0bleu->getX(), agent0bleu->getEquipe());

    _listAgentRouge.push_back(*agent0rouge);
    _carte.setAgent(agent0rouge->getY(), agent0rouge->getX(), agent0rouge);
    _carte.setCase(agent0rouge->getY(), agent0rouge->getX(), agent0rouge->getEquipe());
}

/**
 * @fn Manager::tour
 * @brief Fait agir tous les agents dans un ordre aléatoire.
 */
void Manager::tour()
{
    int nbAgentBleu = _listAgentBleu.size();
    int nbAgentRouge = _listAgentRouge.size();

    int iAgentBleu = 0;
    int iAgentRouge = 0;
    Agent *agentCour = nullptr;

    // Pour chaque agent
    while (iAgentBleu < nbAgentBleu && iAgentRouge < nbAgentRouge)
    {
        // 1 chance sur 2 de choisir un agent d'une équipe
        if (rand() % 2 == 0)
        { // Récupération d'un agent BLEU dans l'odre aléatoire de l'équipe
            agentCour = &(_listAgentBleu[iAgentBleu]);
            ++iAgentBleu;
        }
        else
        { // Récupération d'un agent ROUGE dans l'odre aléatoire de l'équipe
            agentCour = &(_listAgentRouge[iAgentRouge]);
            ++iAgentRouge;
        }
        // Action d'un agent
        actionAgent(agentCour);
    }

    // Si TOUS les agents d'une des deux équipes ont agit
    // Il faut faire agir tous les agents de l'autre équipe qui n'ont pas agit

    // Pour les agents Bleu qui n'ont pas encore agit
    for (int i = iAgentBleu; i < nbAgentBleu; ++i)
    {
        actionAgent(&_listAgentBleu[iAgentBleu]);
    }
    // Pour les agents Rouge qui n'ont pas encore agit
    for (int i = iAgentRouge; i < nbAgentRouge; ++i)
    {
        actionAgent(&_listAgentRouge[iAgentRouge]);
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
 */
void Manager::actionAgent(Agent *agent)
{
    // cout << "Action agent " << (agent->getEquipe() == EQUIPE::BLEU ? "bleu" : "rouge") << endl;

    
    // Récupération du voisinage
    Agent *voisinageAgentVoisins[6]; // Récupération des agents adjacents
    _carte.agentsAdjacents(agent, voisinageAgentVoisins);

    EQUIPE voisinageAgentCases[6]; // Récupération de la couleur des cases adjacentes
    _carte.casesAdjacentes(agent, voisinageAgentCases);

    // Récupère la position de l'agent avant son possible déplacement
    Point pointDepartAgent = agent->getPosition();

    // Action de l'agent
    agent->agir(voisinageAgentVoisins, voisinageAgentCases);

    // Correction de la position de l'agent dans la carte (bord de la map)
    agent->correctionPositionAgent();

    // Nouvelle posistion de l'agent
    Point pointDestinationAgent = agent->getPosition();

    // Mise à jour des grille de la carte
    _carte.deplacerAgent(agent, pointDepartAgent, pointDestinationAgent);

    // Verifier si l'agent a bouge ?? et mettre a nullptr sa pos. -> grille
    // Verifier s'il n'a pas fait de petit

    std::this_thread::sleep_for(500ms);
}

void Manager::afficherCarte()
{
    _carte.afficherCarte();
}

/**
 * @fn Manager::melangerOrdreAgent
 * @brief Mélange l'ordre des agents de chaque équipe dans leurs vecteurs respectifs.
 */
void Manager::melangerOrdreAgent()
{
    fisherYates(_listAgentBleu);
    fisherYates(_listAgentRouge);
}

void fisherYates(vector<Agent> listAgent)
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