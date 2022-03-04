#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

#include "Carte.hpp"
#include "Agent.hpp"
#include "mt.hpp"

using namespace std;

class Manager
{
private:
    vector<Agent *> _listAgents;

    Carte _carte;
    unsigned int _nbAgents;

    // int _nbAgentBleu;
    // int _nbAgentRouge;

public:
    Manager();
    Manager(Agent *agent0Bleu, Agent *agent0Rouge);
    ~Manager();

    void managerInit(Agent *agent0bleu, Agent*agent0rouge);
    void tour();
    void actionAgent(Agent *agent);
    void communicationAgent(Agent *agent);
    void afficherCarte();
    void afficherCarteCarre();

    void updateListAgent(Agent *agentCour,
                         unsigned int &iAgent);

private:
    void melangerOrdreAgent();
};

void fisherYates(vector<Agent *> listagent);

#endif