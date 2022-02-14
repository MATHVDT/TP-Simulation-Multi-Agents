#include "Manager.hpp"

Manager::Manager(Agent &agent0Bleu, Agent &agent0Rouge)
    : _listAgentBleu{agent0Bleu}, _listAgentRouge{agent0Rouge}
{
}

Manager::~Manager()
{
}
