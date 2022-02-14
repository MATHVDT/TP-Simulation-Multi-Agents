/**
 * @enum Direction
 * @brief Direction (enum class)
 * @details
 * Direction de déplacement possible sur depuis une case : 
 * NORDOUEST, OUEST, SUDOUEST, SUDEST, EST, NORDEST 
 */

#ifndef DIRECTION_HPP
#define DIRECTION_HPP

enum class DIRECTION
{
    // Nord, // ↑
    NORDOUEST, // ↖
    OUEST,     // ←
    SUDOUEST,  // ↙
    // Sud, // ↓
    SUDEST,       // ↘
    EST,          // →
    NORDEST,      // ↗
    NULLDIRECTION // X
};

#endif