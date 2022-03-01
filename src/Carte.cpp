#include "Carte.hpp"
#include "Agent.hpp"
#include "Direction.hpp"
#include <iostream>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";

enum class COULEUR : int
{
    RESET = 0,
    RED = 31,
    GREEN = 32,
    BLUE = 34,
    BACKGROUND_BRIGHT_BLEU = 104,
    BACKGROUND_BRIGHT_RED = 101,
    BACKGROUND_RESET = 0
};

const string BACKGROUND_BRIGHT_BLEU = "\033[104m";
const string BACKGROUND_BRIGHT_RED = "\033[101m";
const string BACKGROUND_WHITE = "\033[107m";
const string BACKGROUND_BLACK = "\033[40m";

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

/**
 * @fn Carte::setAgent(int i, int j, Agent *agent)
 * @brief Ajoute un agent dans la carte.
 *
 * @warning La position donnée en paramètre est supposée correcte
 *
 * @param Agent *agent
 */
void Carte::setAgent(int i, int j, Agent *agent)
{
    _grilleAgents[i][j] = agent;
}

/**
 * @fn Carte::setAgent(Agent *agent)
 * @brief Ajoute un agent a la bonne position dans la carte.
 *
 * @warning La position de l'agent est supposée correcte
 *
 * @param Agent *agent
 */
void Carte::setAgent(Agent *agent)
{
    int x = agent->getX();
    int y = agent->getY();

    if (_grilleAgents[y][x])
        throw Carte::ExceptionCaseDejaOccupe();
    else
        setAgent(y, x, agent);
}

// Renvoie true si la couleur de la case à changée
bool Carte::setCase(int i, int j, EQUIPE equipe)
{
    bool res = false;
    res = _grille[i][j] == equipe;
    _grille[i][j] = equipe;
    return res;
}

void Carte::afficherCarte() const
{
    int j;
    int i;

    for (i = 0; i < TAILLE; i++)
    {
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
        cout << endl;
    }
}

bool Carte::estVide(int i, int j) const {
    return _grilleAgents [i][j] == nullptr;
}

//Le résultat de casesAdjacentes est stocké dans un tableau 1D de taille 6 passé en entrée.
//Il représente les 6 points voisins de l'agent passé en entrée.
void Carte::casesAdjacentes(Agent * agent, EQUIPE voisinage[6]) const {
    //Parcours des cases voisines depuis la direction Nord-Ouest en sens trigonométrique
    voisinage[0] = _grille[negMod(agent->getY() - 1, TAILLE)][agent->getX()];
    voisinage[1] = _grille[agent->getY()][negMod(agent->getX() - 1, TAILLE)];
    voisinage[2] = _grille[(agent->getY() + 1) % TAILLE][negMod(agent->getX() - 1, TAILLE)];
    voisinage[3] = _grille[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grille[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grille[negMod(agent->getY() - 1, TAILLE)][(agent->getX() + 1) % TAILLE];
}

//Le résultat de casesAdjacentes est stocké dans un tableau 1D de taille 6 passé en entrée.
//Il représente les 6 points voisins de l'agent passé en entrée.
void Carte::agentsAdjacents(Agent * agent, Agent * voisinage[6]) const {
    //Parcours des cases voisines depuis la direction Nord-Ouest en sens trigonométrique
    voisinage[0] = _grilleAgents[negMod(agent->getY() - 1, TAILLE)][agent->getX()];
    voisinage[1] = _grilleAgents[agent->getY()][(agent->getX() - 1 + TAILLE) % TAILLE];
    voisinage[2] = _grilleAgents[(agent->getY() + 1) % TAILLE][negMod(agent->getX() - 1, TAILLE)];
    voisinage[3] = _grilleAgents[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grilleAgents[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grilleAgents[negMod(agent->getY() - 1, TAILLE)][(agent->getX() + 1) % TAILLE];
}

// Fonctionne avant et apres la MAJ de la position de l'agent
// renvoie true si la case à changée de couleur
bool Carte::deplacerAgent(Agent *agent, Point origine, Point destination)
{
    bool res;
    setAgent(origine.getY(), origine.getX(), nullptr);
    setAgent(destination.getY(), destination.getX(), agent);
    res = setCase(destination.getY(), destination.getX(), agent->getMemoire().getEquipe());

    return res;
}

// A n'utiliser que si l'attribut position de agent est mis à jour après coup
bool Carte::deplacerAgent(Agent *agent, Point Destination)
{
    return deplacerAgent(agent, agent->getPosition(), Destination);
}



// SUpprime l'agent dans la carte => met le pointeur à nullptr
void Carte::suppressionAgent(Agent *agentCour)
{
    agentCour->correctionPositionAgent();
    // Récupère la position de l'agent dans la carte
    int x = agentCour->getX();
    int y = agentCour->getY();

    // Récupère la trace quel'agent laisse quand il meurt
    EQUIPE traceAgentMort = agentCour->getEquipe();

    _grille[y][x] = traceAgentMort;
    _grilleAgents[y][x] = nullptr;
}

int negMod(int n, int mod) {
    return ((n % mod) + mod) % mod;
}