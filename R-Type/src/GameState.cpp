#include "GameState.hpp"
#include "systems/DrawSystem.hpp"
#include "components/Position.hpp"
#include "components/Drawable.hpp"
#include "components/Controllable.hpp"
#include "components/Collidable.hpp"
#include "components/Projectile.hpp"
#include "systems/ControlSystem.hpp"
#include <chrono>

GameState::GameState()
    : rng(std::random_device()()), distX(0.0f, 800.0f), distY(0.0f, 600.0f), distTime(1000, 5000) {
    // Initialize players, enemies, and bullets
}

void GameState::update() {
    registry.run_systems();
    checkCollisions();
    spawnEnemiesRandomly();
}

void GameState::handlePlayerMove(int playerId, float x, float y) {
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
    auto collisions = collision_system(registry, registry.get_components<Position>(), registry.get_components<Drawable>(), registry.get_components<Collidable>(), registry.get_components<Controllable>(), registry.get_components<Projectile>(), is_start);
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