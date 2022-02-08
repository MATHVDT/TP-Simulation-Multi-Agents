/**
 * @file Agent.hpp
 * @brief Fichier entête de la classe Agent.
 */
#ifndef AGENT_HPP
#define AGENT_HPP
#include <iostream>
#include "Direction.hpp"
#include "Memoire.hpp"

using namespace std;

#include "Point.hpp"

enum class EQUIPE;

/**
 * @class Agent
 * @brief Classe Agent
 */
class Agent
{
private:
    static const int _levelMax = 10;

private:
    Point _position;
    int _level;
    Memoire _memoire;

public:
    Agent(int x, int y, EQUIPE equipe);
    Agent(Point position, EQUIPE equipe);

    // Getter
    int getX() const { return _position.getX(); }
    int getY() const { return _position.getY(); }
    Memoire getMemoire() const { return _memoire; }

    // Setter
    void setX(int x) { _position.setX(x); }
    void setY(int y) { _position.setY(y); }

    // Deplacement
    void deplacer(DIRECTION dir);

    void deplacerNordOuest();
    void deplacerOuest();
    void deplacerSudOuest();
    void deplacerSudEst();
    void deplacerEst();
    void deplacerNordEst();

    void partagerMemoireAuVoisinage(Agent *voisinage[6]);
    void partagerMemoireACopain(Agent *copainAdjacent);
    void aquerirMemoire(int level, const Memoire &memoire);
};

#endif