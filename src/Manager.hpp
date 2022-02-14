#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include "Agent.hpp"

class Manager
{
private:
    vector<Agent> _listAgentBleu;
    vector<Agent> _listAgentRouge;


public:
    Manager(Agent &agent0Bleu, Agent &agent0Rouge);
    ~Manager();


};

#endif