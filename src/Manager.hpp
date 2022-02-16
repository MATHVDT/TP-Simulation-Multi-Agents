#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

#include "Carte.hpp"
#include "Agent.hpp"

using namespace std;

class Manager
{
private:
    vector<Agent> _listAgentBleu;
    vector<Agent> _listAgentRouge;

    Carte _carte;

    vector<int> _ordreInteractionBleu;
    vector<int> _ordreInteractionRouge;

public:
    Manager(Agent &agent0Bleu, Agent &agent0Rouge);
    ~Manager();

    void tour();
    void actionAgent(Agent *agent);
    void afficherCarte();
    void updateListAgent(Agent *agentCour,
                         int &iAgentBleu, int &iAgentRouge);

private:
    void melangerOrdreAgent();
};

void fisherYates(vector<Agent> listagent);

#endif