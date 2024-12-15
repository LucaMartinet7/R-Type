#ifndef BULLET_HPP
#define BULLET_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Projectile.hpp"
#include "components/Drawable.hpp"

class Bullet {
public:
    Bullet(Registry& registry, float x, float y, float speed) : registry(registry) {
        entity = registry.spawn_entity();
        registry.add_component<Position>(entity, {x, y});
        registry.add_component<Projectile>(entity, {speed});
        registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(5.0f, 5.0f))});
    }

    Registry::Entity getEntity() const {
        return entity;
    }

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // BULLET_HPP
