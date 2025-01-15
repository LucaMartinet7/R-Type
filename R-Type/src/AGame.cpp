/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** AGame
*/

#include "GameState.hpp"
#include "Network/Packet.hpp"
#include "Network/PacketType.hpp"
#include "Server.hpp"
#include "AGame.hpp"
#include <algorithm>
#include <iostream>


AGame::~AGame()
{
    playerActions.clear();
    players.clear();
    enemies.clear();
    bullets.clear();
}

void AGame::addPlayerAction(int playerId, int actionId) {
    std::cout << "Player " << playerId << " performed action " << actionId << std::endl;
    playerActions.emplace_back(playerId, actionId);
}

void AGame::processPlayerActions() {
    for (auto& action : playerActions) {
        int playerId = action.getId();
        int actionId = action.getActionId();

        if (actionId > 0 && actionId < 5) { // Change by real action ID defined in server
            handlePlayerMove(playerId, actionId);
            action.setProcessed(true);
        } else if (actionId == 5) { // Change by real action ID defined in server
            spawnBullet(playerId);
            action.setProcessed(true);
        }
        // Handle other actions or ignore unknown action IDs 
    }
    deletePlayerAction();
}

void AGame::deletePlayerAction() { //deletes all process elements from the vector of player actions and resizes vector
    playerActions.erase(
        std::remove_if(playerActions.begin(), playerActions.end(),
            [](const PlayerAction& action) { return action.getProcessed(); }),
        playerActions.end());
}

const std::vector<PlayerAction>& AGame::getPlayerActions() const {
    return playerActions;
}

std::pair<float, float> AGame::getPlayerPosition(int playerId) const {
    if (playerId < 0 || playerId >= players.size()) {
        throw std::out_of_range("Invalid player ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[players[playerId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

std::pair<float, float> AGame::getEnemyPosition(int enemyId) const {
    if (enemyId < 0 || enemyId >= enemies.size()) {
        throw std::out_of_range("Invalid enemy ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[enemies[enemyId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

std::pair<float, float> AGame::getBulletPosition(int bulletId) const {
    if (bulletId < 0 || bulletId >= bullets.size()) {
        throw std::out_of_range("Invalid bullet ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[bullets[bulletId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

std::pair<float, float> AGame::getBossPosition(int bossId) const {
    if (bossId < 0 || bossId >= bosses.size()) {
        throw std::out_of_range("Invalid boss ID");
    }

    const auto& positionComponent = registry.get_components<Position>()[bosses[bossId].getEntity()];
    return {positionComponent->x, positionComponent->y};
}

void GameState::spawnEnemy(float x, float y) {
    enemies.emplace_back(registry, x, y);

    Enemy& lastEnemy = enemies.back();
    Registry::Entity lastEnemyId = lastEnemy.getEntity();

    std::string data = std::to_string(lastEnemyId) + ";" + std::to_string(x) + ";" + std::to_string(y);
    m_server->Broadcast(m_server->createPacket(Network::PacketType::CREATE_ENEMY, data));
}

void GameState::spawnBoss(float x, float y) {
    bosses.emplace_back(registry, x, y);

    Boss& lastBoss = bosses.back();
    Registry::Entity lastBossId = lastBoss.getEntity();

    std::string data = std::to_string(lastBossId) + ";" + std::to_string(x) + ";" + std::to_string(y);
    m_server->Broadcast(m_server->createPacket(Network::PacketType::CREATE_BOSS, data));
}

void GameState::spawnPlayer(int playerId, float x, float y) {
    if (playerId >= 0 && playerId < 4) {
        players.emplace_back(registry, x, y);

        Player& lastPlayer = players.back();
        Registry::Entity lastPlayerId = lastPlayer.getEntity();

        std::string data = std::to_string(playerId) + ";" + std::to_string(lastPlayerId) + ";" + std::to_string(x) + ";" + std::to_string(y);
        m_server->Broadcast(m_server->createPacket(Network::PacketType::CREATE_PLAYER, data));
    }
}

void GameState::spawnBullet(int playerId) {
    if (playerId < players.size()) {
        auto entity = players[playerId].getEntity();
        if (registry.has_component<Position>(entity)) {
            const auto& position = registry.get_components<Position>()[entity];
            bullets.emplace_back(registry, position->x + 50.0f, position->y + 25.0f, 1.0f);

            Bullet& lastBullet = bullets.back();
            Registry::Entity lastBulletId = lastBullet.getEntity();

            std::string data = std::to_string(lastBulletId) + ";" + std::to_string(position->x + 50.0f) + ";" + std::to_string(position->y + 25.0f);
            m_server->Broadcast(m_server->createPacket(Network::PacketType::CREATE_BULLET, data));
        } else {
            std::cerr << "Error: Player " << playerId << " does not have a Position component." << std::endl;
        }
    }
}

// Provide definitions for the pure virtual functions in AGame
void AGame::spawnPlayer(int playerId, float x, float y) {
    // Implementation can be empty or provide a default behavior
}

void AGame::spawnEnemy(float x, float y) {
    // Implementation can be empty or provide a default behavior
}

void AGame::spawnBullet(int playerId) {
    // Implementation can be empty or provide a default behavior
}

void AGame::spawnBoss(float x, float y) {
    // Implementation can be empty or provide a default behavior
}