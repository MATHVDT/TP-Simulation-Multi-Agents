/**
 * @file Point.hpp
 * @brief Fichier de la classe Point *inutilisée*.
 */
#ifndef POINT_HPP
#define POINT_HPP

/**
 * @class Point
 * @brief Classe représentant des coordonnées 2D.
 */
class Point
{
private:
    int _x;
    int _y;

public:
    Point(int x, int y);

    int getX() const { return _x; }
    int getY() const { return _y; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
};

#endif