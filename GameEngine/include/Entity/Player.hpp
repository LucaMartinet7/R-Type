#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Drawable.hpp"
#include "components/Controllable.hpp"
#include "components/Collidable.hpp"

class Player {
public:
    Player(Registry& registry, float x, float y) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Velocity>(entity, {0.0f, 0.0f});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
        registry.add_component<Controllable>(entity, {});
        registry.add_component<Collidable>(entity, {true});
    }

    Registry::Entity getEntity() const {
        return entity;
    }

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // PLAYER_HPP
