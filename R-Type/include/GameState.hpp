/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** GameState
*/

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Registry.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "PlayerAction.hpp"
#include <vector>
#include <random>

class GameState {
public:
    GameState();

    void update();
    void handlePlayerMove(int playerId, int actionId);
    void spawnPlayer(int playerId, float x, float y);
    void spawnEnemy(float x, float y);
    void shootBullet(int playerId);
    size_t getPlayerCount() const;

    void addPlayerAction(int playerId, int actionId);
    void processPlayerActions();
    void deletePlayerAction();
    const std::vector<PlayerAction>& getPlayerActions() const;

    //get_players_position dans Game qui hérite de AGame. TOutes les fonctions pour que server envoie bien au client
    //process_player_actions dans AGame qui hérite de IGame
    //add_player_actions ça dans AGame qui hérite de IGame
    //delete_player_actions dans AGame qui hérite de IGame

private:
    Registry registry;
    std::vector<Player> players;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<PlayerAction> playerActions;
    std::mt19937 rng;
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;
    std::uniform_int_distribution<int> distTime;

    void checkCollisions();
    void spawnEnemiesRandomly();
};

#endif // GAME_STATE_HPP