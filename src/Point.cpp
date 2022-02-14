#include "Point.hpp"

/**
 * @fn Point::Point(int x, int y)
 * @param int x - *Coordonnée x du point*
 * @param int y - *Coordonnée y du point*
 */
Point::Point(int x, int y) : _x(x), _y(y) {}

/**
 * @fn Point operator+(const Point &p1, const Point &p2)
 * @brief Surcharge operateur + pour deux points.
 */
Point operator+(const Point &p1, const Point &p2)
{
    Point res{p1.getX() + p2.getX(),
              p1.getY() + p2.getY()};
    return res;
}

/**
 * @fn Point directionToPoint(DIRECTION direction)
 * @brief Convertie une direction en point.
 * @param DIRECTION direction
 */
Point directionToPoint(DIRECTION direction)
{
    int x = 0;
    int y = 0;
    switch (direction)
    {
    case DIRECTION::NORDOUEST: // ↖
        y = -1;
        break;
    case DIRECTION::OUEST: // ←
        x = -1;
        break;
    case DIRECTION::SUDOUEST: // ↙
        x = -1;
        y = 1;
        break;
    case DIRECTION::SUDEST: // ↘
        y = 1;
        break;
    case DIRECTION::EST: // →
        x = 1;
        break;
    case DIRECTION::NORDEST: // ↗
        x = 1;
        y = -1;
        break;
    case DIRECTION::NULLDIRECTION: // X
        x = 0;
        y = 0;
        break;
    }

    Point p{x, y};
    return p;
}

/**
 * @fn DIRECTION pointToDirection(Point point)
 * @brief Convertie un point en une direction.
 * @param Point point
 */
DIRECTION pointToDirection(Point point)
{
    DIRECTION dir = DIRECTION::NULLDIRECTION;

    int x = point.getX();
    int y = point.getY();

    if (x == -1)
    {
        if (y == 1)
        {
            dir = DIRECTION::SUDOUEST;
        }
        else
        {
            dir = DIRECTION::OUEST;
        }
    }
    else if (x == 1)
    {
        if (y == -1)
        {
            dir = DIRECTION::NORDEST;
        }
        else
        {
            dir = DIRECTION::EST;
        }
    }
    else // x = 0
    {
        if (y == -1)
        {
            dir = DIRECTION::NORDOUEST;
        }
        else if (y == 1)
        {
            dir = DIRECTION::SUDEST;
        }
    }

    return dir;
}
