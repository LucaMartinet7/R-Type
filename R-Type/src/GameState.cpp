/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** GameState
*/

#include "GameState.hpp"
#include "DrawSystem.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Controllable.hpp"
#include "Collidable.hpp"
#include "Projectile.hpp"
#include "ControlSystem.hpp"
#include <chrono>
#include <algorithm>

GameState::GameState()
    : rng(std::random_device()()), distX(0.0f, 800.0f), distY(0.0f, 600.0f), distTime(1000, 5000) {}

void GameState::update() {
    registry.run_systems();
    checkCollisions();
    spawnEnemiesRandomly();
    processPlayerActions(); 
}

void GameState::handlePlayerMove(int playerId, int actionId) { // move player depending on action done by player
    float moveDistance = 10.0f; // Change this value for different movement speeds
    float x = 0.0f;
    float y = 0.0f;

    if (actionId == 1) { // Left
        x = -moveDistance;
    } else if (actionId == 2) { // Right
        x = moveDistance;
    } else if (actionId == 3) { // Up
        y = -moveDistance;
    } else if (actionId == 4) { // Down
        y = moveDistance;
    }

    players[playerId].move(x, y);
}

void GameState::spawnPlayer(int playerId, float x, float y) {
    if (playerId >= 0 && playerId < 4) {
        players.emplace_back(registry, x, y);
    }
}

void GameState::spawnEnemy(float x, float y) {
    enemies.emplace_back(registry, x, y);
}

void GameState::shootBullet(int playerId) {
    const auto& position = registry.get_components<Position>()[players[playerId].getEntity()];
    bullets.emplace_back(registry, position->x + 50.0f, position->y + 25.0f, 1.0f);
}

void GameState::checkCollisions() {
    auto collisions = collision_system(registry, registry.get_components<Position>(), registry.get_components<Drawable>(), registry.get_components<Collidable>(), registry.get_components<Controllable>(), registry.get_components<Projectile>());
    for (const auto& [entity1, entity2] : collisions) {
        if (registry.get_components<Controllable>()[entity1]) {
            registry.kill_entity(entity1);
        }
        if (registry.get_components<Controllable>()[entity2]) {
            registry.kill_entity(entity2);
        }
    }
}

void GameState::spawnEnemiesRandomly() {
    static auto lastSpawnTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSpawnTime).count();

    if (elapsed > distTime(rng)) {
        float x = distX(rng);
        float y = distY(rng);
        spawnEnemy(x, y);
        lastSpawnTime = now;
    }
}

size_t GameState::getPlayerCount() const {
    return players.size();
}

std::pair<float, float> GameState::getPlayerPosition(int playerId) const {
    if (playerId < 0 || playerId >= players.size()) {
        throw std::out_of_range("Invalid player ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[players[playerId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

std::pair<float, float> GameState::getEnemyPosition(int enemyId) const {
    if (enemyId < 0 || enemyId >= enemies.size()) {
        throw std::out_of_range("Invalid enemy ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[enemies[enemyId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

std::pair<float, float> GameState::getBulletPosition(int bulletId) const {
    if (bulletId < 0 || bulletId >= bullets.size()) {
        throw std::out_of_range("Invalid bullet ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[bullets[bulletId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}
