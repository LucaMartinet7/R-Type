/*
** EPITECH PROJECT, 2024
** R-type ECS
** File description:
** Draw System
*/

#ifndef DRAWSYSTEM_H
    #define DRAWSYSTEM_H

#include "Registry.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @brief Renders all drawable entities in the game window.
 * @param registry The registry managing entities and their components.
 * @param window The SFML render window where entities are drawn.
 * @param positions Sparse array of position components.
 * @param drawables Sparse array of drawable components.
 * @details This system iterates through all entities with position and drawable components,
 * sets the position of the drawable shapes, and renders them in the provided SFML window.
 */
inline void draw_system(
    Registry& registry,
    sf::RenderWindow& window,
    sparse_array<Position>& positions,
    sparse_array<Drawable>& drawables) {

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto& pos = positions[i];
        auto& drawable = drawables[i];
        if (pos && drawable) {
            drawable->shape.setPosition(pos->x, pos->y);
            window.draw(drawable->shape);
        }
    }
}

#endif // DRAWSYSTEM_H
