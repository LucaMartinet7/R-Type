#include "Enemy.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Collidable.hpp"

Enemy::Enemy(Registry& registry, float x, float y) : registry(registry) {
    entity = registry.spawn_entity();
    registry.add_component<Position>(entity, {x, y});
    registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Collidable>(entity, {true});
}

Registry::Entity Enemy::getEntity() const {
    return entity;
}