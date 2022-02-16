#include "Manager.hpp"

Manager::Manager(Agent &agent0Bleu, Agent &agent0Rouge)
    : _listAgentBleu{agent0Bleu}, _listAgentRouge{agent0Rouge},
      _carte{&agent0Bleu, &agent0Rouge},
      _ordreInteractionBleu{0}, _ordreInteractionRouge{0}
{
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
    int nbAgentBleu = _listAgentBleu.size();
    int nbAgentRouge = _listAgentRouge.size();
    // Indice de parcours des vecteurs des agents
    int iAgentBleu = 0;
    int iAgentRouge = 0;
    // Quelle équipe est choisie
    bool agentBleuChoisi = false;
    // bool agentRougeChoisi = false;

    Agent *agentCour = nullptr;
    bool agentVivant = true;

    // Pour chaque agent
    while (iAgentBleu < _listAgentBleu.size() && iAgentRouge < _listAgentRouge.size())
    {
        // 1 chance sur 2 de choisir un agent d'une équipe
        if (rand() % 2 == 0)
        { // Récupération d'un agent BLEU dans l'odre aléatoire de l'équipe
            agentCour = &(_listAgentBleu[iAgentBleu]);
            agentBleuChoisi = true;
        }
        else
        { // Récupération d'un agent ROUGE dans l'odre aléatoire de l'équipe
            agentCour = &(_listAgentRouge[iAgentRouge]);
            agentBleuChoisi = false;
            // agentRougeChoisi=true;
        }
        // Action d'un agent
        actionAgent(agentCour);

        updateListAgent(agentCour, iAgentBleu, iAgentRouge);

        }

    // Si TOUS les agents d'une des deux équipes ont agit
    // Il faut faire agir tous les agents de l'autre équipe qui n'ont pas agit

    // Pour les agents Bleu qui n'ont pas encore agit
    for (int i = iAgentBleu; i < _listAgentBleu.size(); ++i)
    {
        actionAgent(&_listAgentBleu[iAgentBleu]);
    }
    // Pour les agents Rouge qui n'ont pas encore agit
    for (int i = iAgentRouge; i < _listAgentRouge.size(); ++i)
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
//  * @return bool *Agent vivant*
 */
void Manager::actionAgent(Agent *agent)
{
    // cout << "Action agent " << (agent->getEquipe() == EQUIPE::BLEU ? "bleu" : "rouge") << endl;
    // Par défaut on ne retire pas d'agent => agent reste en vie
    bool agentVivant = true;

    // Récupération du voisinage
    Agent *voisinageAgentVoisins[6]; // Récupération des agents adjacents
    _carte.agentsAdjacents(agent, voisinageAgentVoisins);

    EQUIPE voisinageAgentCases[6]; // Récupération de la couleur des cases adjacentes
    _carte.casesAdjacentes(agent, voisinageAgentCases);

    // Récupère la position de l'agent avant son possible déplacement
    Point pointDepartAgent = agent->getPosition();

    // Action de l'agent
    agent->agir(voisinageAgentVoisins, voisinageAgentCases);
    agentVivant = !(agent->getAction() == ACTION::MORT);

    // Agent toujours en vie, on le tient à jour dans la carte
    if (agentVivant)
    {
        // Nouvelle posistion de l'agent
        Point pointDestinationAgent = agent->getPosition();

        // Correction de la position de l'agent dans la carte (bord de la map)
        _carte.correctionPositionAgent(agent);

        // Mise à des grille de la carte
        _carte.deplacerAgent(agent, pointDepartAgent, pointDestinationAgent);
    }

    // Verifier si l'agent a bouge ?? et mettre a nullptr sa pos. -> grille
    // Verifier s'il n'a pas fait de petit

    // _carte.afficherCarte();
    // std::this_thread::sleep_for(50ms);
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

// SUpprime l'agent de la car si besoin
void Manager::updateListAgent(Agent *agentCour,
                              int &iAgentBleu, int &iAgentRouge)
{
    // Récupération de l'état de mort de l'agent ou pas
    bool agentMort = agentCour->getAction() == ACTION::MORT;
    // Récupération de son équipe
    bool agentBleuChoisi = agentCour->getEquipe() == EQUIPE::BLEU;

    if (agentMort) // Agent mort
    {
        // Suppression de l'agent dans la carte
        // ...
        // _carte.suppressionAgent(agentCour);

        // suppression dans les vecteur
        if (agentBleuChoisi)
            _listAgentBleu.erase(_listAgentBleu.begin() + iAgentBleu);
        else
            _listAgentRouge.erase(_listAgentRouge.begin() + iAgentRouge);

        // delete agentCour ???
        delete agentCour;
    }
    else // Agent pas mort : Trop fort ce gars en faite !!! 
    {
        // Incrémentation des indices de parcours
        agentBleuChoisi ? ++iAgentBleu : ++iAgentRouge;
    }
}
