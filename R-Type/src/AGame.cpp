/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** AGame
*/

#include "GameState.hpp"
#include "AGame.hpp"
#include <algorithm>
#include <iostream>

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
            shootBullet(playerId);
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
