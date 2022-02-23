#include <iostream>
#include <vector>

#include "Manager.hpp"

using namespace std;

int main()
{
cout << "\033[100m";
    Agent *agent0Bleu = new Agent{0, 0, EQUIPE::BLEU};
    Agent *agent0Rouge = new Agent{40, 4, EQUIPE::ROUGE};

    agent0Rouge->gagneLevel(1);

    Manager manager{agent0Bleu, agent0Rouge};
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

    // const string BACKGROUND_BRIGHT_BLEU = "\033[104m";
    // const string GREEN = "\033[32m";

    // string b = BACKGROUND_BRIGHT_BLEU;
    // string bb = "\033[103m";

    // cout << b << GREEN << "hello" << endl;
    // cout << bb << GREEN << "hello" << endl;

    return 0;
}