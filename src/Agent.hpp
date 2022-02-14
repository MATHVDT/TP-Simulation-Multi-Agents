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
enum class ACTION;

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
    ACTION _action;

public:
    Agent(int x, int y, EQUIPE equipe);
    Agent(Point position, EQUIPE equipe);

    // Getter
    Point getPosition() const { return _position; }
    int getX() const { return _position.getX(); }
    int getY() const { return _position.getY(); }
    int getLevel() const { return _level; }
    EQUIPE getEquipe() const { return getMemoire().getEquipe(); }
    Memoire getMemoire() const { return _memoire; }

    // Setter
    void setX(int x) { _position.setX(x); }
    void setY(int y) { _position.setY(y); }

    // Deplacement
    void deplacer(DIRECTION dir);

    void partagerMemoireAuVoisinage(Agent *voisinage[6]);
    void partagerMemoireACopain(Agent *copainAdjacent);
    void aquerirMemoire(int level, const Memoire &memoire);

    Point agir(Agent *voisinage[6]);

    Agent &operator=(const Agent & agent);
};

enum class ACTION
{
    DIVISION,
    DEPLACEMENT,
    RENFORCEMENT,
    ESTATTAQUE,
    MORT,
    INACTIF
};

#endif