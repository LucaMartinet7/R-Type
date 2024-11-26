//
// Created by noe on 26/11/2024.
//

#ifndef POSITIONSYSTEM_H
    #define POSITIONSYSTEM_H

#include "Registry.h"
#include "Position.h"
#include "Velocity.h"

void position_system(Registry& registry) {
    auto& positions = registry.get_components<Position>();
    auto& velocities = registry.get_components<Velocity>();

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