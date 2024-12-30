/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Velocity
*/

#ifndef VELOCITY_H
    #define VELOCITY_H

/*!
 * @struct Velocity
 * @brief Represents the velocity of an entity in 2D space.
 * @details This structure stores the velocity components along the X and Y axes, used for movement.
 */
struct Velocity {
    /*!
     * @brief The velocity along the X-axis.
     */
    float vx;

    /*!
     * @brief The velocity along the Y-axis.
     */
    float vy;
};

#endif // VELOCITY_H
