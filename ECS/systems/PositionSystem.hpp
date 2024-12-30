/*
** EPITECH PROJECT, 2024
** R-type ECS
** File description:
** Position System
*/

#ifndef POSITIONSYSTEM_H
    #define POSITIONSYSTEM_H

#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"

/*!
 * @brief Updates the positions of entities based on their velocities.
 * @param registry The registry managing entities and their components.
 * @param positions Sparse array of position components.
 * @param velocities Sparse array of velocity components.
 * @details This system iterates through all entities with position and velocity components,
 * updating their positions by adding their velocity components to their current positions.
 */
inline void position_system(
    Registry& registry,
    sparse_array<Position>& positions,
    sparse_array<Velocity>& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto& pos = positions[i];
        auto& vel = velocities[i];
        if (pos && vel) {
            pos->x += vel->vx;
            pos->y += vel->vy;
        }
    }
}

#endif // POSITIONSYSTEM_H
