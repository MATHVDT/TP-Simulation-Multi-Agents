#include <iostream>
#include <vector>

#include "Manager.hpp"

using namespace std;

int main()
{

    Agent agent0Bleu{0,0, EQUIPE::BLEU};
    Agent agent0Rouge{4,4, EQUIPE::ROUGE};

    Manager manager{agent0Bleu, agent0Rouge};

    manager.tour();

    return 0;
}