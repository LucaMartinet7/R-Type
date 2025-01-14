#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop() {}

void GameLoop::initialize(int numPlayers) {
  	gameState.registerComponents();
    for (int i = 0; i < numPlayers; ++i) {
        gameState.spawnPlayer(i, 100.0f * (i + 1), 100.0f);
    }
    gameState.startNextWave();
}

void GameLoop::start() {
    std::thread gameThread(&GameLoop::run, this);
    gameThread.detach();
}

void GameLoop::run() {
    while (true) {
        // Handle player input (for testing purposes, we move player 0 to the right)
        if (0 < gameState.getPlayerCount()) {
            gameState.handlePlayerMove(0, 1.0f, 0.0f);
        } else {
            std::cerr << "Player 0 does not exist." << std::endl;
        }

        // Update game state
        gameState.update();

        // Check if all enemies are cleared and start the next wave or spawn the boss
        if (gameState.areEnemiesCleared()) {
            if (gameState.isBossSpawned()) {
                std::cout << "Boss defeated! Game over." << std::endl;
                break;
            } else if (gameState.currentWave >= 3) {
                gameState.spawnBoss(400.0f, 300.0f); // Spawn boss at the center of the screen
            } else {
                gameState.startNextWave();
            }
        }

        // Sleep for a short duration to simulate frame time
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

GameState& GameLoop::getGameState() {
    return gameState;
}