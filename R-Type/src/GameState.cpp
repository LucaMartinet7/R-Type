#include "Server.hpp"
#include "GameState.hpp"
#include "AGame.hpp"
#include "CollisionSystem.hpp"
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

GameState::GameState(RType::Server* server)
    : rng(std::random_device()()), distX(0.0f, 800.0f), distY(0.0f, 600.0f),
      distTime(1000, 5000), currentWave(0), enemiesPerWave(5) {}

void GameState::initializeplayers(int numPlayers) {
    registerComponents();
    for (int i = 0; i < numPlayers; ++i) {
        spawnPlayer(i, 100.0f * (i + 1.0f), 100.0f);
    }
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
    processPlayerActions();
}

void GameState::run(int numPlayers) {
    initializeplayers(numPlayers);
    while (true) {
        // Update game state
        update();

        // Check if all enemies are cleared and start the next wave or spawn the boss
        // if (areEnemiesCleared()) {
        //     if (isBossSpawned()) {
        //         std::cout << "Boss defeated! Game over." << std::endl;
        //         break;
        //     } else if (currentWave >= 3) {
        //         spawnBoss(400.0f, 300.0f); // Spawn boss at the center of the screen
        //     } else {
        //         startNextWave();
        //     }
        // }

        // Sleep for a short duration to simulate frame time
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void GameState::handlePlayerMove(int playerId, int actionId) {
    float moveDistance = 1.0f;
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

bool GameState::isBossSpawned() const {
    return !bosses.empty();
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
        bool isEnemy2 = std::find_if(enemies.begin(), enemies.end(),
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

size_t GameState::getPlayerCount() const {
    return players.size();
}

size_t GameState::getEnemiesCount() const {
    return enemies.size();
}

size_t GameState::getBulletsCount() const {
    return bullets.size();
}

Registry& GameState::getRegistry() {
    return registry;
}

size_t GameState::getBossCount() const {
    return bosses.size();
}