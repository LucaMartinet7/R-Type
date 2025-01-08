#include "../../include/Entity/Player.hpp"

Player::Player(Registry& registry, float x, float y) : registry(registry) {
    entity = registry.spawn_entity();
    registry.add_component<Position>(entity, {x, y});
    registry.add_component<Velocity>(entity, {0.0f, 0.0f});
    registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Controllable>(entity, {});
    registry.add_component<Collidable>(entity, {true});
}

void Player::move(float x, float y) {
    auto& pos = registry.get_components<Position>()[entity];
    pos->x += x;
    pos->y += y;
}

Registry::Entity Player::getEntity() const {
    return entity;
}