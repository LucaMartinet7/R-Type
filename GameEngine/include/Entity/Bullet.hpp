#ifndef BULLET_HPP
#define BULLET_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Projectile.hpp"
#include "components/Drawable.hpp"

/*!
 * @class Bullet
 * @brief Represents a bullet entity in the game.
 * @details Handles the creation and initialization of a bullet with position, projectile, and drawable components.
 */
class Bullet {
public:
    /*!
     * @brief Constructs a new Bullet object.
     * @param registry The ECS registry.
     * @param x The initial x-coordinate of the bullet.
     * @param y The initial y-coordinate of the bullet.
     * @param speed The speed of the bullet.
     */
    Bullet(Registry& registry, float x, float y, float speed) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Projectile>(entity, {speed});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(5.0f, 5.0f))});
    }

    /*!
     * @brief Retrieves the entity ID of the bullet.
     * @return The entity ID.
     */
    Registry::Entity getEntity() const {
        return entity;
    }

private:
    Registry& registry; /*!< Reference to the ECS registry. */
    Registry::Entity entity; /*!< The entity representing the bullet. */
};

#endif // BULLET_HPP
