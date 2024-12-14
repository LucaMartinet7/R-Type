/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** ProjectileSystem
*/

#ifndef PROJECTILESYSTEM_H
    #define PROJECTILESYSTEM_H

#include "Registry.h"
#include "Position.h"
#include "Projectile.h"
#include "Drawable.h"

void projectile_system(Registry& registry, sparse_array<Position>& positions, sparse_array<Projectile>& projectiles, sparse_array<Drawable>& drawables) {
    for (size_t i = 0; i < positions.size() && i < projectiles.size() && i < drawables.size(); ++i) {
        auto& pos = positions[i];
        auto& proj = projectiles[i];
        auto& drawable = drawables[i];
        if (pos && proj && drawable) {
            pos->x += proj->speed;
            if (pos->x > 800) { // window width
                registry.kill_entity(i);
            }
        }
    }
}

#endif // PROJECTILESYSTEM_H
