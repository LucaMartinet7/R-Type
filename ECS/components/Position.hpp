/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Position
*/

#ifndef POSITION_H
    #define POSITION_H

/*!
 * @struct Position
 * @brief Represents the position of an entity in 2D space.
 * @details This structure is used to store the X and Y coordinates of an entity.
 */
struct Position {
    /*!
     * @brief The X coordinate of the entity.
     */
    float x;

    /*!
     * @brief The Y coordinate of the entity.
     */
    float y;
};

#endif // POSITION_H
