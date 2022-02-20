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

    public:
        Manager();
        ~Manager();

        void managerInit(Agent *agent0bleu, Agent*agent0rouge);
        void tour();
        void actionAgent(Agent *agent);
        void afficherCarte();

    private:
        void melangerOrdreAgent();
};


void fisherYates(vector<Agent> listagent);

#endif