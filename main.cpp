#include "Carte.hpp"
#include <iostream>

using namespace std;

int main()
{
    Carte carte{};

    carte.AfficherCarte();
    cout << "-----" << endl;
    carte.ChangerCase(3, 6, 10);
    carte.ChangerCase(7, 7, 7);
    carte.AfficherCarte();

    return 0;
}