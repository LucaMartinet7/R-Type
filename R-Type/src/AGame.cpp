/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** AGame
*/

#include "AGame.hpp"
#include <algorithm>

void AGame::addPlayerAction(int playerId, int actionId) {
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
