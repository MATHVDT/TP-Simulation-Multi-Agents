#include "Carte.hpp"
#include "Agent.hpp"
#include "Direction.hpp"
#include <iostream>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";

Carte::Carte()
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            _grille[i][j] = EQUIPE::NEUTRE;
            _grilleAgents[i][j] = nullptr;
        }
    }
}

void Carte::afficherCarte() const
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
        //if (i % 2 == 1) cout << " ";
        for (j = 0; j < i; j++)
        {
            std::cout << " ";
        }
        for (j = 0; j < TAILLE; j++)
        {
            if (_grilleAgents[i][j] != nullptr)
            {
                switch (_grilleAgents[i][j]->getMemoire().getEquipe())
                {
                    case EQUIPE::ROUGE:
                        std::cout << RED << "A ";
                        break;
                    case EQUIPE::BLEU:
                        std::cout << BLUE << "A ";
                        break;
                    default:
                    std::cout << GREEN << "E ";
                        break;
                }
            }
            else
            {
                switch (_grille[i][j])
                {
                    case EQUIPE::NEUTRE:
                        std::cout << RESET << ". ";
                        break;
                    case EQUIPE::ROUGE:
                        std::cout << RED << ". ";
                        break;
                    case EQUIPE::BLEU:
                        std::cout << BLUE << ". ";
                        break;
                    default:
                    std::cout << RESET << "? ";
                        break;
                }
            }
            
        }
        std::cout << endl;
    }
}

Agent * Carte::getAgent(int i, int j) const {
    return _grilleAgents[i][j];
}

void Carte::setAgent(int i, int j, Agent * agent) {
    _grilleAgents[i][j] = agent;
}

void Carte::changerCase(int i, int j, EQUIPE equipe) {
    _grille[i][j] = equipe;
}

bool Carte::estVide(int i, int j) const {
    return _grilleAgents [i][j] == nullptr;
}

void Carte::casesAdjacentes(Agent * agent, EQUIPE voisinage[3][2]) const {
    int x, y;

    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 3; y++)
        {
            voisinage[y][x] = _grille[y + agent->getY()][x + agent->getX()];
        }
    }
}

void Carte::agentsAdjacents(Agent * agent, Agent * voisinage[3][2]) const {
    int x, y;

    for (x = 0; x < 2; x++)
    {
        for (y = 0; y < 3; y++)
        {
            voisinage[y][x] = _grilleAgents[y + agent->getY()][x + agent->getX()];
        }
    }
}

void Carte::deplacerAgent(Agent * agent, Point origine, Point destination)
{
    setAgent(origine.getY(), origine.getX(), nullptr);
    setAgent(destination.getY(), destination.getX(), agent);
    changerCase(destination.getY(), destination.getX(), agent->getMemoire().getEquipe());
}

void Carte::deplacerAgent(Agent * agent, Point Destination) {
    deplacerAgent(agent, agent->getPosition(), Destination);
}