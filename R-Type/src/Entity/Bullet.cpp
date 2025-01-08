//
// Created by noe on 08/01/2025.
//
#include "../../include/Entity/Bullet.hpp"

Bullet::Bullet(Registry& registry, float x, float y, float speed) : registry(registry) {
    entity = registry.spawn_entity();
    registry.add_component<Position>(entity, {x, y});
    registry.add_component<Projectile>(entity, {speed});
    registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(5.0f, 5.0f))});
}

Registry::Entity Bullet::getEntity() const {
    return entity;
}