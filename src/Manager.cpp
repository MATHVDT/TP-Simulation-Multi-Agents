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

void Manager::tour()
{
    int nbAgentBleu = _listAgentBleu.size();
    int nbAgentRouge = _listAgentRouge.size();

    int iAgentBleu = 0;
    int iAgentRouge = 0;
    Agent *agentCour;

    // Pour chaque agent
    while (iAgentBleu < nbAgentBleu && iAgentRouge < nbAgentRouge)
    { // 1 chance sur 2 de choisir un agent d'une équipe
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

void Manager::actionAgent(Agent *agent)
{
    cout << "Action agent " << (agent->getEquipe() == EQUIPE::BLEU ? "bleu" : "rouge") << endl;
}

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