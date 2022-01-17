#include "Carte.hpp"
#include <iostream>

using namespace std;

Carte::Carte()
{
    int j;
    int i;

    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {
            _grille[i][j] = 0;
        }
    }
}

void Carte::AfficherCarte()
{
    int j;
    int i;

    for (i = 0; i < taille; i++)
    {
        if (i % 2 == 1) cout << " ";
        for (j = 0; j < taille; j++)
        {
            switch (_grille[i][j])
            {
                case 0:
                    cout << ". ";
                    break;
                case 10:
                    cout << "A ";
                    break;
                default:
                cout << "? ";
                    break;
            }
        }
        cout << endl;
    }
}

void Carte::ChangerCase(int i, int j, int val)
{
    _grille[i][j] = val;
}