#include <iostream>
#include <vector>

#include "Manager.hpp"

using namespace std;

int main()
{
    Agent agent0Bleu{3, 2, EQUIPE::BLEU};
    Agent agent0Rouge{4, 4, EQUIPE::ROUGE};

    Manager manager{};

    manager.managerInit(&agent0Bleu, &agent0Rouge);

    manager.afficherCarte();
    cout << "-----" << endl;
    for (int i = 0; i < 10; ++i)
    {
        manager.tour();
        manager.afficherCarte();
        cout << "-----" << endl;
        std::this_thread::sleep_for(2000ms);
    }
    return 0;
}