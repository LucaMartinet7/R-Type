/*
** EPITECH PROJECT, 2024
** CPP-Rtype
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_H
    #define COLLISIONSYSTEM_H

#include "Registry.hpp"
#include "Position.hpp"
#include "Collidable.hpp"
#include "Drawable.hpp"
#include "Projectile.hpp"
#include "Controllable.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

/*!
 * @brief Checks if two rectangle shapes are colliding.
 * @param shape1 The first rectangle shape.
 * @param shape2 The second rectangle shape.
 * @return True if the shapes are colliding, false otherwise.
 */
inline bool check_collision(const sf::RectangleShape& shape1, const sf::RectangleShape& shape2) {
    return shape1.getGlobalBounds().intersects(shape2.getGlobalBounds());
}

/*!
 * @brief Processes collisions in the entity-component system (ECS).
 * @param registry The registry managing entities and their components.
 * @param positions Sparse array of position components.
 * @param drawables Sparse array of drawable components.
 * @param collidables Sparse array of collidable components.
 * @param controllables Sparse array of controllable components.
 * @param projectiles Sparse array of projectile components.
 * @param is_start A flag indicating whether the collision check is performed at the start of the game.
 * @return A vector of pairs of indices representing the entities involved in collisions.
 * @details This function iterates through all entities with position, drawable, and collidable components,
 * checks for collisions between them, and handles the effects of the collisions (e.g., killing entities).
 */
inline std::vector<std::pair<size_t, size_t>> collision_system(
    Registry& registry,
    sparse_array<Position>& positions,
    sparse_array<Drawable>& drawables,
    sparse_array<Collidable>& collidables,
    sparse_array<Controllable>& controllables,
    sparse_array<Projectile>& projectiles,
    bool is_start) {

    std::vector<std::pair<size_t, size_t>> collisions;

    for (size_t i = 0; i < positions.size() && i < drawables.size() && i < collidables.size(); ++i) {
        auto& pos = positions[i];
        auto& drawable = drawables[i];
        auto& collidable = collidables[i];
        if (pos && drawable && collidable && collidable->is_collidable) {
            for (size_t j = i + 1; j < positions.size() && j < drawables.size() && j < collidables.size(); ++j) {
                auto& otherPos = positions[j];
                auto& otherDrawable = drawables[j];
                auto& otherCollidable = collidables[j];
                if (otherPos && otherDrawable && otherCollidable && otherCollidable->is_collidable) {
                    if (check_collision(drawable->shape, otherDrawable->shape)) {
                        // Avoid immediate collision at the start
                        if (is_start) {
                            continue;
                        }
                        collisions.emplace_back(i, j); // Record collision
                        if (controllables[i] || controllables[j]) {
                            registry.kill_entity(controllables[i] ? i : j);
                        }
                        if (projectiles[i] || projectiles[j]) {
                            registry.kill_entity(projectiles[i] ? j : i);
                            registry.kill_entity(projectiles[i] ? i : j);
                        } else {
                            if (!controllables[i] && !controllables[j]) {
                                registry.kill_entity(i);
                                registry.kill_entity(j);
                            }
                        }
                    }
                }
            }
        }
    }

    return collisions; // Return list of collisions
}

#endif // COLLISIONSYSTEM_H
