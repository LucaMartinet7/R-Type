/*
** EPITECH PROJECT, 2024
** R-type ECS
** File description:
** Position System
*/

#ifndef POSITIONSYSTEM_H
    #define POSITIONSYSTEM_H

#include "Registry.h"
#include "Position.h"
#include "Velocity.h"

inline void position_system(Registry& registry, sparse_array<Position>& positions, sparse_array<Velocity>& velocities) {
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