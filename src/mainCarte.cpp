#include "Carte.hpp"
#include "Agent.hpp"
#include <iostream>

using namespace std;

int main()
{
    Carte carte{};

    carte.afficherCarte();
    cout << "-----" << endl;
    carte.changerCase(3, 6, 1);
    carte.changerCase(7, 7, 7);
    for (int i  = 3; i < 7; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            carte.changerCase(i, j, 2);
        }
    }
    Agent * agent1 = new Agent(5, 5);
    carte.setAgent(agent1->getX(), agent1->getY(), agent1);
    carte.afficherCarte();


    return 0;
}