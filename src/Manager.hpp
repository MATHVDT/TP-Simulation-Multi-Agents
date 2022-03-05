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

    static Manager *_singleton;

private:
    Manager();

public:
    ~Manager();

    static Manager *getInstance();

    void managerInit(Agent *agent0bleu,
                     Agent *agent0rouge);

    void simulation(int nbTour);
    void simulationAnimee(int nbTour,
                          std::chrono::milliseconds frameTpsMs);
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