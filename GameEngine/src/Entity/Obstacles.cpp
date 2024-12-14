#include "Obstacles.hpp"

Obstacles::Obstacles(int x, int y, const std::string& asset, Registry& registry)
    : registry(registry) {
    if (!_obstaclesText.loadFromFile(asset)) {
        std::cerr << "Error: Could not load obstacle texture!" << std::endl;
    }

    _obstaclesSprite.setTexture(_obstaclesText);
    _obstaclesSprite.setPosition(x, y);

    // Add to ECS registry
    obstacleEntity = registry.spawn_entity();
    registry.add_component<Position>(obstacleEntity, {x, y});
    registry.add_component<Drawable>(obstacleEntity, {_obstaclesSprite});
    registry.add_component<Collidable>(obstacleEntity, {true});
}