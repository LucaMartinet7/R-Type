/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Entity
*/

#ifndef ENTITY_H
  #define ENTITY_H

#include <cstddef>

/*!
 * @class Entity
 * @brief Represents an entity in the ECS (Entity Component System).
 * @details Each entity is uniquely identified by an ID, allowing it to be associated with components.
 */
class Entity {
  public:
    /*!
     * @brief Constructs a new Entity object with a given ID.
     * @param id The unique identifier for the entity.
     */
    explicit Entity(std::size_t id) : id(id) {}

    /*!
     * @brief Converts the Entity object to its unique identifier.
     * @return The ID of the entity as a std::size_t.
     */
    operator std::size_t() const { return id; }

  private:
    /*!
     * @brief The unique identifier for the entity.
     */
    std::size_t id;
};

#endif //ENTITY_H
