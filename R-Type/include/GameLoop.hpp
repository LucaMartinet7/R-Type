#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include "GameState.hpp"
#include <thread>
#include <chrono>

class GameLoop {
public:
    GameLoop();
    void start();
    void initialize(int numPlayers);
    GameState& getGameState();

private:
    GameState gameState;
    void run();
};

#endif // GAME_LOOP_HPP