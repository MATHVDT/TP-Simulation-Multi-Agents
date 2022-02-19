#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Carte.hpp"
#include "Agent.hpp"

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
    Manager(Agent *agent0Bleu, Agent *agent0Rouge);
    ~Manager();

    void afficherCarte();
    void afficherSfml(sf::RenderWindow &window,
                      const int largeurWindow,
                      const int hauteurWindow) const;

    void tour(sf::RenderWindow& window );
    void actionAgent(Agent *agent);
    void updateListAgent(Agent *agentCour,
                         unsigned int &iAgent);

private:
    void melangerOrdreAgent();
};

void fisherYates(vector<Agent *> listagent);

#endif