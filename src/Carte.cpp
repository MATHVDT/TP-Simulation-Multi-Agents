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

Agent *Carte::getAgent(int i, int j) const
{
    return _grilleAgents[i][j];
}

void Carte::setAgent(int i, int j, Agent *agent)
{
    _grilleAgents[i][j] = agent;
}

/**
 * @fn Carte::setAgent(Agent *agent)
 * @brief Ajoute un agent dans la carte.
 *
 * @warning La position de l'agent est supposée correcte
 *
 * @param Agent *agent
 */
void Carte::setAgent(Agent *agent)
{
    int x = agent->getX();
    int y = agent->getY();

    // Vérification de la disponibilité de la case
    if (_grilleAgents[y][x])
        throw Carte::ExceptionCaseDejaOccupe();

    _grilleAgents[y][x] = agent;
}

void Carte::setCase(int i, int j, EQUIPE equipe)
{
    _grille[i][j] = equipe;
}

void Carte::afficherCarte() const
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
        // if (i % 2 == 1) cout << " ";
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

bool Carte::estVide(int i, int j) const {
    return _grilleAgents [i][j] == nullptr;
}

//Le résultat de casesAdjacentes est stocké dans un tableau 1D de taille 6 passé en entrée.
//Il représente les 6 points voisins de l'agent passé en entrée.
void Carte::casesAdjacentes(Agent * agent, EQUIPE voisinage[6]) const {
    //Parcours des cases voisines depuis la direction Nord-Ouest en sens trigonométrique
    voisinage[0] = _grille[(agent->getY() - 1) % TAILLE][agent->getX()];
    voisinage[1] = _grille[agent->getY()][(agent->getX() - 1) %TAILLE];
    voisinage[2] = _grille[(agent->getY() + 1) % TAILLE][(agent->getX() - 1) % TAILLE];
    voisinage[3] = _grille[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grille[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grille[(agent->getY() - 1) % TAILLE][(agent->getX() + 1) % TAILLE];
}

//Le résultat de casesAdjacentes est stocké dans un tableau 1D de taille 6 passé en entrée.
//Il représente les 6 points voisins de l'agent passé en entrée.
void Carte::agentsAdjacents(Agent * agent, Agent * voisinage[6]) const {
    //Parcours des cases voisines depuis la direction Nord-Ouest en sens trigonométrique
    voisinage[0] = _grilleAgents[(agent->getY() - 1) % TAILLE][agent->getX()];
    voisinage[1] = _grilleAgents[agent->getY()][(agent->getX() - 1) %TAILLE];
    voisinage[2] = _grilleAgents[(agent->getY() + 1) % TAILLE][(agent->getX() - 1) % TAILLE];
    voisinage[3] = _grilleAgents[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grilleAgents[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grilleAgents[(agent->getY() - 1) % TAILLE][(agent->getX() + 1) % TAILLE];
}

//A utiliser avant de mettre à jour
void Carte::deplacerAgent(Agent * agent, Point origine, Point destination)
{
    correctionPositionAgent(agent);
    setAgent(origine.getY(), origine.getX(), nullptr);
    setAgent(destination.getY(), destination.getX(), agent);
    setCase(destination.getY(), destination.getX(), agent->getMemoire().getEquipe());
}

// A n'utiliser que si l'attribut position de agent est mis à jour après coup
void Carte::deplacerAgent(Agent *agent, Point Destination)
{
    deplacerAgent(agent, agent->getPosition(), Destination);
}

/**
 * @fn void Carte::correctionPositionAgent
 * @brief Corrige la position de l'agent pour qu'il reste dans la Carte.
 *
 * @param Agent *agent - *Agent à qui il faut corriger la position*
 */
void Carte::correctionPositionAgent(Agent *agent)
{
    agent->setX((agent->getX() + TAILLE) % TAILLE);
    agent->setY((agent->getY() + TAILLE) % TAILLE);
}

// SUpprime l'agent dans la carte => met le pointeur à nullptr
void Carte::suppressionAgent(Agent *agentCour)
{
    correctionPositionAgent(agentCour);
    // Récupère la position de l'agent dans la carte
    int x = agentCour->getX();
    int y = agentCour->getY();

    // Récupère la trace quel'agent laisse quand il meurt
    // EQUIPE traceAgentMort = agentCour->getTraceMort();

    // _grille[y][x] = traceAgentMort;
    _grilleAgents[y][x] = nullptr;
}