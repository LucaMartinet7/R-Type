#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Registry.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Boss.hpp"
#include <vector>
#include <random>

class GameState {
public:
    GameState();

    void update();
    void handlePlayerMove(int playerId, float x, float y);
    void spawnPlayer(int playerId, float x, float y);
    void spawnEnemy(float x, float y);
    void shootBullet(int playerId);
    void spawnBoss(float x, float y);
    size_t getPlayerCount() const;
    bool isBossSpawned() const;
    bool areEnemiesCleared() const;
    void startNextWave();
    Registry &getRegistry();
    void registerComponents();

    int currentWave;

private:
    Registry registry;
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::unique_ptr<Boss> boss;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;
    std::uniform_int_distribution<int> distTime;
    int enemiesPerWave;

    void checkCollisions();
    void spawnEnemiesRandomly();
};

#endif // GAME_STATE_HPP