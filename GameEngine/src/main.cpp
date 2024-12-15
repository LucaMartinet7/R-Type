//
// Created by noe on 26/11/2024.
//

#include <iostream>
#include "Game.hpp"

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}