#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Drawable.hpp"
#include "components/Collidable.hpp"

/*!
 * @class Enemy
 * @brief Represents an enemy entity in the game.
 * @details Handles the creation and initialization of an enemy with position, drawable, and collidable components.
 */
class Enemy {
public:
    /*!
     * @brief Constructs a new Enemy object.
     * @param registry The ECS registry.
     * @param x The initial x-coordinate of the enemy.
     * @param y The initial y-coordinate of the enemy.
     */
    Enemy(Registry& registry, float x, float y) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
        registry.add_component<Collidable>(entity, {true});
    }

    /*!
     * @brief Retrieves the entity ID of the enemy.
     * @return The entity ID.
     */
    Registry::Entity getEntity() const {
        return entity;
    }

private:
    Registry& registry; /*!< Reference to the ECS registry. */
    Registry::Entity entity; /*!< The entity representing the enemy. */
};

#endif // ENEMY_HPP
