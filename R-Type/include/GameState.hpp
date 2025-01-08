#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Registry.hpp"
#include "Entity/Player.hpp"
#include "Entity/Enemy.hpp"
#include "Entity/Bullet.hpp"
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

private:
    Registry registry;
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;
    std::uniform_int_distribution<int> distTime;

    void checkCollisions();
    void spawnEnemiesRandomly();
};

#endif // GAME_STATE_HPP