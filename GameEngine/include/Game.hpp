/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Game
*/

#ifndef GAME_H
    #define GAME_H

#include <SFML/Graphics.hpp>
#include "components/Entity.hpp"
#include "Registry.hpp"
#include "Layers/Menu.hpp"
#include "Entity/Enemy.hpp"

/*!
 * @class Game
 * @brief Represents the core game logic and main loop.
 * @details Manages the game state, entities, and systems, and handles rendering and user input.
 */
class Game {
public:
    /*!
     * @brief Constructs a new Game object.
     * @details Initializes components, entities, systems, and the game menu.
     */
    Game();

    /*!
     * @brief Starts the main game loop.
     * @details The loop handles event processing, updating game logic, and rendering.
     */
    void run();

private:
    /*!
     * @brief Processes user input and window events.
     */
    void processEvents();

    /*!
     * @brief Updates game state and runs all registered systems.
     */
    void update();

    /*!
     * @brief Renders the current game state or menu.
     */
    void render();

    /*!
     * @brief Handles player input events, such as mouse button presses.
     * @param button The mouse button that was pressed.
     * @param isPressed Whether the button is pressed or released.
     */
    void handlePlayerInput(sf::Mouse::Button button, bool isPressed);

    /*!
     * @brief Spawns and sets up a new bullet entity.
     */
    void shoot();

    Registry registry; /*!< The ECS registry managing entities and components. */
    sf::RenderWindow window; /*!< The SFML render window for the game. */
    sf::Font font; /*!< Font used for text rendering. */
    sf::RectangleShape startButton; /*!< The start button for the game menu. */
    bool gameStarted; /*!< Whether the game has started. */
    bool is_start; /*!< Whether the game is in its initial state. */
    bool hasPlayers; /*!< Whether there are any players remaining in the game. */
    Registry::Entity controllableEntity; /*!< The entity controlled by the player. */
    Menu menu; /*!< The game menu. */
};

#endif // GAME_H
