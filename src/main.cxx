#include <iostream>
#include <vector>

#include "Manager.hpp"
#include "Generateur.hpp"

using namespace std;

int main()
{

    Generateur::initGen();

    Agent *agent0Bleu = new Agent{0, 0, EQUIPE::BLEU};
    Agent *agent0Rouge = new Agent{1, 4, EQUIPE::ROUGE};

    agent0Bleu->setX(rand() % TAILLE);
    agent0Bleu->setY(rand() % TAILLE);
    agent0Rouge->setX(rand() % TAILLE);
    agent0Rouge->setY(rand() % TAILLE);

    // agent0Rouge->gagneLevel(1);
    // agent0Bleu->gagneLevel();

    Manager manager{agent0Bleu, agent0Rouge};

    manager.afficherCarte();
    std::this_thread::sleep_for(2000ms);

    try
    {

        manager.afficherCarte();
        for (int i = 0; i < 10000; ++i)
        {
            cerr << "tour " << i << endl;
            manager.tour();
            manager.afficherCarte();
            std::this_thread::sleep_for(50ms);
            system("clear");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    manager.afficherCarte();

    return 0;
}