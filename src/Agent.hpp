#ifndef AGENT_HPP
#define AGENT_HPP

#include "Point.hpp"

class Agent
{
private:
    Point _position;

public:
    Agent(Point point);
    Agent(int x, int y);

    Point getPosition() const { return _position; }
    int getX() const { return _position.getX(); }
    int getY() const { return _position.getY(); }

    void setPosition(Point &point) { _position = point; }
    void setX(int x) { _position.setX(x); }
    void setY(int y) { _position.setY(y); }
};

#endif