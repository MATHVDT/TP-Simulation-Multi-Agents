/**
 * @enum Direction
 * @brief Direction (enum class)
 * @details
 * Direction de déplacement possible sur depuis une case
 */

#ifndef DIRECTION_HPP
#define DIRECTION_HPP

enum class DIRECTION
{
    // Nord, // ↑
    NORDOUEST, // ↖
    OUEST, // ←
    SUDOUEST, // ↙ 
    // Sud, // ↓
    SUDEST, // ↘
    EST, // →
    NORDEST // ↗
};

#endif