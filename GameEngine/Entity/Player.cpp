#include "Player.hpp"

Player::Player(Registry& registry, int x, int y, const std::string& asset)
    : registry(registry) {
    playerEntity = registry.spawn_entity();
    registry.add_component<Position>(playerEntity, {x, y});
    registry.add_component<Velocity>(playerEntity, {0.0f, 0.0f});
    registry.add_component<Drawable>(playerEntity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Controllable>(playerEntity, {});
    registry.add_component<Collidable>(playerEntity, {true});

    if (!_playerText.loadFromFile(asset)) {
        std::cerr << "Can't find the image" << std::endl;
    }
    _playerSprite.setPosition(x, y);
    _playerSprite.setTexture(_playerText);
    _playerSprite.setScale(1.4, 1.4);
}