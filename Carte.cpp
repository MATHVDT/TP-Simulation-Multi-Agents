#include "Carte.hpp"
#include <iostream>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";

Carte::Carte()
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            _grille[i][j] = 0;
            _grilleAgents[i][j] = nullptr;
        }
    }
}

void Carte::AfficherCarte() const
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
        if (i % 2 == 1) cout << " ";
        for (j = 0; j < TAILLE; j++)
        {
            if (_grilleAgents[i][j] != nullptr)
            {
                
            }
            else
            {
                switch (_grille[i][j])
                {
                    case 0:
                        cout << RESET << ". ";
                        break;
                    case 1:
                        cout << RED << ". ";
                        break;
                    case 2:
                        cout << GREEN << ". ";
                        break;
                    default:
                    cout << RESET << "? ";
                        break;
                }
            }
            
        }
        cout << endl;
    }
}

Agent * Carte::getAgent(int i, int j) {
    return _grilleAgents[i][j];
}

void Carte::setAgent(int i, int j, Agent * agent) {
    _grilleAgents[i][j] = agent;
}

void Carte::ChangerCase(int i, int j, int val)
{
    _grille[i][j] = val;
}