#include "Carte.hpp"
#include "Agent.hpp"
#include "Direction.hpp"
#include <iostream>

using namespace std;

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";

Carte::Carte(Agent *agent0Bleu, Agent *agent0Rouge)
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
    _grilleAgents[agent0Bleu->getY()][agent0Bleu->getX()] = agent0Bleu;
    _grilleAgents[agent0Rouge->getY()][agent0Rouge->getX()] = agent0Rouge;
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

Agent *Carte::getAgent(int i, int j) const
{
    return _grilleAgents[i][j];
}

void Carte::setAgent(int i, int j, Agent *agent)
{
    _grilleAgents[i][j] = agent;
}

void Carte::changerCase(int i, int j, EQUIPE equipe)
{
    _grille[i][j] = equipe;
}

bool Carte::estVide(int i, int j) const
{
    return _grilleAgents[i][j] == nullptr;
}

void Carte::casesAdjacentes(Agent *agent, EQUIPE voisinage[6]) const
{
    voisinage[0] = _grille[(agent->getY() - 1) % TAILLE][agent->getX()];
    voisinage[1] = _grille[agent->getY()][(agent->getX() - 1) % TAILLE];
    voisinage[2] = _grille[(agent->getY() + 1) % TAILLE][(agent->getX() - 1) % TAILLE];
    voisinage[3] = _grille[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grille[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grille[(agent->getY() - 1) % TAILLE][(agent->getX() + 1) % TAILLE];
}

void Carte::agentsAdjacents(Agent *agent, Agent *voisinage[6]) const
{
    voisinage[0] = _grilleAgents[(agent->getY() - 1) % TAILLE][agent->getX()];
    voisinage[1] = _grilleAgents[agent->getY()][(agent->getX() - 1) % TAILLE];
    voisinage[2] = _grilleAgents[(agent->getY() + 1) % TAILLE][(agent->getX() - 1) % TAILLE];
    voisinage[3] = _grilleAgents[(agent->getY() + 1) % TAILLE][agent->getX()];
    voisinage[4] = _grilleAgents[agent->getY()][(agent->getX() + 1) % TAILLE];
    voisinage[5] = _grilleAgents[(agent->getY() - 1) % TAILLE][(agent->getX() + 1) % TAILLE];
}

void Carte::deplacerAgent(Agent *agent, Point origine, Point destination)
{
    setAgent(origine.getY(), origine.getX(), nullptr);
    setAgent(destination.getY(), destination.getX(), agent);
    changerCase(destination.getY(), destination.getX(), agent->getMemoire().getEquipe());
}

// Pas sur que ca serve ...
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
    agent->setX(agent->getX() % TAILLE);
    agent->setY(agent->getY() % TAILLE);
}

// SUpprime l'agent dans la carte => met le pointeur à nullptr
void Carte::suppressionAgent(Agent *agentCour)
{
    // Récupère la position de l'agent dans la carte
    int x = agentCour->getX();
    int y = agentCour->getY();

    // Récupère la trace quel'agent laisse quand il meurt
    EQUIPE traceAgentMort = agentCour->getTraceMort();

    _grille[y][x] = traceAgentMort;
    _grilleAgents[y][x] = nullptr;
}

// ----------------- //

void Carte::afficherCarteSfml(
    sf::RenderWindow &window,
    const int largeurWindow,
    const int hauteurWindow) const
{
    int j;
    int i;

    int minTailleWindow = min(hauteurWindow, largeurWindow);
    // int minTailleWindow = largeurWindow;
    float rayon = (float)minTailleWindow / (2.f + 1.5 * (float)TAILLE);
    rayon = 0.9 * rayon;
    // Case
    sf::CircleShape caseHexa{rayon, 6};
    caseHexa.setFillColor(sf::Color::White);

    // Agent
    sf::CircleShape agent{rayon / 2.f};
    agent.setOutlineThickness(3.f);
    agent.setOutlineColor(sf::Color::White);

    // Position
    sf::Vector2f positionCaseHexa{0.f, 0.f};
    sf::Vector2f offSetPositionAgent{18.f, 18.f};

    float decalageX, decalageY;

    for (i = 0; i < TAILLE; i++)
    {

        decalageX = (float)i * 0.95 * rayon;
        decalageY = (float)i * 1.6 * rayon;
        positionCaseHexa.y = decalageY;

        for (j = 0; j < TAILLE; j++)
        {
            if (_grilleAgents[i][j] != nullptr)
            {
                agent.setOutlineColor(sf::Color::Black);
                switch (_grilleAgents[i][j]->getMemoire().getEquipe())
                {
                case EQUIPE::ROUGE:
                    agent.setFillColor(sf::Color(178, 34, 34));
                    break;
                case EQUIPE::BLEU:
                    agent.setFillColor(sf::Color::Blue);
                    break;
                default:
                    agent.setFillColor(sf::Color::Black);
                    break;
                }
            }
            else
            {
                agent.setOutlineColor(sf::Color::Transparent);
                agent.setFillColor(sf::Color::Transparent);
            }
            switch (_grille[i][j])
            {
            case EQUIPE::NEUTRE:
                caseHexa.setFillColor(sf::Color::White);
                break;
            case EQUIPE::ROUGE:
                caseHexa.setFillColor(sf::Color(255, 99, 71));
                break;
            case EQUIPE::BLEU:
                caseHexa.setFillColor(sf::Color(30, 144, 255));
                break;
            default:
                // std::cout << RESET << "? ";
                break;
            }

            // Set de la position X
            positionCaseHexa.x = decalageX + (float)j * 1.85 * rayon;

            // Set position de la case et de l'agent
            caseHexa.setPosition(positionCaseHexa);
            agent.setPosition(positionCaseHexa + offSetPositionAgent);

            // Dessin
            window.draw(caseHexa);
            window.draw(agent);
        }
    }
}
