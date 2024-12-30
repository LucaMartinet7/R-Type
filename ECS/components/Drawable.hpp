/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Drawable
*/

#ifndef DRAWABLE_H
    #define DRAWABLE_H

#include <SFML/Graphics.hpp>

/*!
 * @struct Drawable
 * @brief Represents a drawable component for rendering entities.
 * @details This structure is used to define graphical attributes of an entity, allowing it to be rendered on the screen.
 */
struct Drawable {
    /*!
     * @brief The shape representing the entity's graphical representation.
     * @details Uses SFML's RectangleShape to define the entity's visual attributes.
     */
    sf::RectangleShape shape;
};

#endif // DRAWABLE_H
