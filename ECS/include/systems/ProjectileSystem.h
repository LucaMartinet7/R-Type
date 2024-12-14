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
#include "Collidable.h"

inline void projectile_system(Registry& registry, sparse_array<Position>& positions, sparse_array<Projectile>& projectiles, sparse_array<Drawable>& drawables, sparse_array<Collidable>& collidables) {
    for (size_t i = 0; i < positions.size() && i < projectiles.size() && i < drawables.size() && i < collidables.size(); ++i) {
        auto& pos = positions[i];
        auto& proj = projectiles[i];
        auto& drawable = drawables[i];
        auto& collidable = collidables[i];
        if (pos && proj && drawable && collidable) {
            pos->x += proj->speed;
            if (pos->x > 800) { // window width
                registry.kill_entity(i);
                continue;
            }
            for (size_t j = 0; j < positions.size() && j < drawables.size() && j < collidables.size(); ++j) {
                if (i == j) continue;
                auto& otherPos = positions[j];
                auto& otherDrawable = drawables[j];
                auto& otherCollidable = collidables[j];
                if (otherPos && otherDrawable && otherCollidable && otherCollidable->is_collidable) {
                    if (drawable->shape.getGlobalBounds().intersects(otherDrawable->shape.getGlobalBounds())) {
                        registry.kill_entity(i);
                        registry.kill_entity(j);
                        break;
                    }
                }
            }
        }
    }
}

#endif // PROJECTILESYSTEM_H
