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
    : rng(std::random_device()()), distX(0.0f, 800.0f), distY(0.0f, 600.0f), distTime(1000, 5000) {
    // Initialize players, enemies, and bullets
}

void GameState::addPlayerAction(int playerId, int actionId) {
    playerActions.emplace_back(playerId, actionId);
}

void GameState::processPlayerActions() {
    for (auto& action : playerActions) {
        int playerId = action.getId();
        int actionId = action.getActionId();

        if (actionId > 0 && actionId < 5) { // Change by real action ID defined in server
            handlePlayerMove(playerId, actionId);
            action.setProcessed(true);
        } else if (actionId == 5) { // Change by real action ID defined in server
            shootBullet(playerId);
            action.setProcessed(true);
        }
        // Handle other actions or ignore unknown action IDs 
    }
    deletePlayerAction();
}

void GameState::deletePlayerAction() { //deletes all process elements from the vector of player actions and resizes vector
    playerActions.erase(
        std::remove_if(playerActions.begin(), playerActions.end(),
            [](const PlayerAction& action) { return action.getProcessed(); }),
        playerActions.end());
}

const std::vector<PlayerAction>& GameState::getPlayerActions() const {
    return playerActions;
}

void GameState::update() {
    registry.run_systems();
    checkCollisions();
    spawnEnemiesRandomly();
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
