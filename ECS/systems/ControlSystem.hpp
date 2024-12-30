/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Control System
*/

#ifndef CONTROLSYSTEM_H
    #define CONTROLSYSTEM_H

#include "Registry.hpp"
#include "Velocity.hpp"
#include "Controllable.hpp"
#include <SFML/Window.hpp>
#include "CollisionSystem.hpp"

/*!
 * @brief Updates the velocities of controllable entities based on player input.
 * @param registry The registry managing entities and their components.
 * @param velocities Sparse array of velocity components.
 * @param controllables Sparse array of controllable components.
 * @param positions Sparse array of position components (not used in this function but included for potential extensions).
 * @param drawables Sparse array of drawable components (not used in this function but included for potential extensions).
 * @param collidables Sparse array of collidable components (not used in this function but included for potential extensions).
 * @details This system iterates over all entities with velocity and controllable components
 * and updates their velocities based on keyboard input (e.g., arrow keys).
 */
inline void control_system( Registry& registry, sparse_array<Velocity>& velocities, sparse_array<Controllable>& controllables, sparse_array<Position>& positions, sparse_array<Drawable>& drawables, sparse_array<Collidable>& collidables) {
    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto& vel = velocities[i];
        auto& ctrl = controllables[i];
        if (vel && ctrl) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                vel->vx = -0.125f;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                vel->vx = 0.125f;
            } else {
                vel->vx = 0.0f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                vel->vy = -0.125f;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                vel->vy = 0.125f;
            } else {
                vel->vy = 0.0f;
            }
        }
    }
}

#endif // CONTROLSYSTEM_H
