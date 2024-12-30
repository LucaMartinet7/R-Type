/*
** EPITECH PROJECT, 2024
** CPP-Rtype
** File description:
** Collidable
*/

#ifndef COLLIDABLE_H_
    #define COLLIDABLE_H_

    /*!
     * @struct Collidable
     * @brief Represents a collidable component for an entity.
     * @details This structure is used to define whether an entity can collide with others in the game.
     */
    struct Collidable {
        /*!
         * @brief Constructs a new Collidable object.
         * @param is_collidable A boolean indicating whether the entity is collidable. Defaults to true.
         */
        Collidable(bool is_collidable = true) : is_collidable(is_collidable) {}

        /*!
         * @brief Indicates if the entity is collidable.
         */
        bool is_collidable;
    };

#endif /* !COLLIDABLE_H_ */
