#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Drawable.hpp"
#include "Controllable.hpp"
#include "Collidable.hpp"

/*!
 * @class Player
 * @brief Represents the player entity in the game.
 * @details Handles the creation and initialization of a player with position, velocity, drawable, controllable, and collidable components.
 */
class Player {
public:
    /*!
     * @brief Constructs a new Player object.
     * @param registry The ECS registry.
     * @param x The initial x-coordinate of the player.
     * @param y The initial y-coordinate of the player.
     */
    Player(Registry& registry, float x, float y) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Velocity>(entity, {0.0f, 0.0f});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
        registry.add_component<Controllable>(entity, {});
        registry.add_component<Collidable>(entity, {true});
    }

    /*!
     * @brief Retrieves the entity ID of the player.
     * @return The entity ID.
     */
    Registry::Entity getEntity() const {
        return entity;
    }

    /*!
     * @brief Retrieves the registry managing the player.
     * @return The ECS registry.
     */
    Registry getRegistry() const {
        return registry;
    }
    
private:
    Registry& registry; /*!< Reference to the ECS registry. */
    Registry::Entity entity; /*!< The entity representing the player. */
};

#endif // PLAYER_HPP
