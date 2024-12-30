//
// Created by noe on 26/11/2024.
//

#include <iostream>
#include "Game.hpp"

/*!
 * @brief Entry point for the R-Type game.
 * @details Initializes the game and starts the main game loop. Catches any exceptions and logs errors.
 * @return Returns 0 on successful execution, or -1 if an exception is thrown.
 */
int main() {
    try {
        /*!
         * @brief Creates the Game object and starts the game loop.
         */
        Game game;
        game.run();
    } catch (const std::exception& e) {
        /*!
         * @brief Handles exceptions by printing the error message to the standard error stream.
         * @param e The exception caught.
         */
        std::cerr << "Exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
