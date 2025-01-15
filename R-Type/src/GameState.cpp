#include "GameState.hpp"
#include "DrawSystem.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Controllable.hpp"
#include "Collidable.hpp"
#include "Projectile.hpp"
#include "ControlSystem.hpp"
#include <chrono>

GameState::GameState()
    : rng(std::random_device()()), distX(0.0f, 800.0f), distY(0.0f, 600.0f), distTime(1000, 5000), boss(nullptr), currentWave(0), enemiesPerWave(5) {
    registerComponents();
}

void GameState::registerComponents() {
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Collidable>();
    registry.register_component<Projectile>();
}

void GameState::update() {
    registry.run_systems();
    //checkCollisions();
    spawnEnemiesRandomly();

    if (boss) { // handle the slow movement of the boss
        boss->move(0.1f, 0.0f);
    }
}

void GameState::handlePlayerMove(int playerId, float x, float y) {
    if (playerId < players.size()) {
        players[playerId].move(x, y);
    }
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
    if (playerId < players.size()) {
        auto entity = players[playerId].getEntity();
        if (registry.has_component<Position>(entity)) {
            const auto& position = registry.get_components<Position>()[entity];
            bullets.emplace_back(registry, position->x + 50.0f, position->y + 25.0f, 1.0f);
        } else {
            std::cerr << "Error: Player " << playerId << " does not have a Position component." << std::endl;
        }
    }
}

void GameState::spawnBoss(float x, float y) {
    boss = std::make_unique<Boss>(registry, x, y);
}

bool GameState::isBossSpawned() const {
    return boss != nullptr;
}

bool GameState::areEnemiesCleared() const {
    return enemies.empty();
}

void GameState::startNextWave() {
    currentWave++;
    enemiesPerWave += 5; // Increase the number of enemies per wave
    for (int i = 0; i < enemiesPerWave; ++i) {
        spawnEnemy(distX(rng), distY(rng));
    }
}

void GameState::checkCollisions() {
    auto collisions = collision_system(
        registry,
        registry.get_components<Position>(),
        registry.get_components<Drawable>(),
        registry.get_components<Collidable>(),
        registry.get_components<Controllable>(),
        registry.get_components<Projectile>()
    );

    for (const auto& [entity1, entity2] : collisions) {
        bool isProjectile1 = registry.has_component<Projectile>(entity1);
        bool isProjectile2 = registry.has_component<Projectile>(entity2);
        bool isPlayer1 = registry.has_component<Controllable>(entity1);
        bool isPlayer2 = registry.has_component<Controllable>(entity2);
        bool isEnemy1 = std::find_if(enemies.begin(), enemies.end(),
            [entity1](auto& e){ return e.getEntity() == entity1; }) != enemies.end();
        bool isEnemy2      = std::find_if(enemies.begin(), enemies.end(),
            [entity2](auto& e){ return e.getEntity() == entity2; }) != enemies.end();

        // Projectile <-> Enemy
        if (isProjectile1 && isEnemy2) {
            registry.kill_entity(entity1);
            registry.kill_entity(entity2);
        } else if (isProjectile2 && isEnemy1) {
            registry.kill_entity(entity1);
            registry.kill_entity(entity2);
        }

        // Player <-> Enemy
        if (isPlayer1 && isEnemy2) {
            registry.kill_entity(entity1);
        } else if (isPlayer2 && isEnemy1) {
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

Registry& GameState::getRegistry()
{
    return registry;
}
