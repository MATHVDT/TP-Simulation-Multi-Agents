#include "Carte.hpp"
#include <iostream>

using namespace std;

int main()
{
    Carte carte{};

    carte.AfficherCarte();
    cout << "-----" << endl;
    carte.ChangerCase(3, 6, 1);
    carte.ChangerCase(7, 7, 7);
    for (int i  = 3; i < 7; i++)
    {
        for (int j = 2; j < 5; j++)
        {
            carte.ChangerCase(i, j, 2);
        }
    }
    carte.AfficherCarte();

    return 0;
}