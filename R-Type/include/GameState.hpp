/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** GameState
*/

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "AGame.hpp"
#include "Registry.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "PlayerAction.hpp"
#include <vector>
#include <random>

class GameState : public AGame {
public:
    GameState();

    void update() override;
    void handlePlayerMove(int playerId, int actionId) override;
    void spawnPlayer(int playerId, float x, float y) override;
    void spawnEnemy(float x, float y) override;
    void shootBullet(int playerId) override;
    size_t getPlayerCount() const override;
    size_t getEnemiesCount() const override;
    size_t getBulletsCount() const override;

private:
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;
    std::uniform_int_distribution<int> distTime;

    void checkCollisions();
    void spawnEnemiesRandomly();
};

#endif // GAME_STATE_HPP