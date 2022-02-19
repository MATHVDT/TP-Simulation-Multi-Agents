#include <iostream>
#include <vector>

#include "Manager.hpp"

using namespace std;

int main()
{

    Agent *agent0Bleu = new Agent{1, 1, EQUIPE::BLEU};
    Agent *agent0Rouge = new Agent{3, 3, EQUIPE::ROUGE};

    Manager manager{agent0Bleu, agent0Rouge};

    manager.afficherCarte();
    for (int i = 0; i < 20; ++i)
    {
        // system("clear");
        cout << "tour " << i << endl;
        manager.tour();
        manager.afficherCarte();
        std::this_thread::sleep_for(100ms);
    }
    manager.afficherCarte();

    return 0;
}