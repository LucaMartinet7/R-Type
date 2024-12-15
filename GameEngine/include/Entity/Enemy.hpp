#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Drawable.hpp"
#include "components/Collidable.hpp"

class Enemy {
public:
    Enemy(Registry& registry, float x, float y) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
        registry.add_component<Collidable>(entity, {true});
    }

    Registry::Entity getEntity() const {
        return entity;
    }

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // ENEMY_HPP
