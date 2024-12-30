#include "Game.hpp"
#include "systems/DrawSystem.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Drawable.hpp"
#include "components/Controllable.hpp"
#include "components/Collidable.hpp"
#include "components/Projectile.hpp"
#include "systems/PositionSystem.hpp"
#include "systems/ControlSystem.hpp"
#include "systems/ProjectileSystem.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Layers/Menu.hpp"
#include <iostream>

/*!
 * @class Game
 * @brief Manages the main game loop and its systems.
 * @details This class handles initialization, updating, rendering, and input processing for the R-Type game.
 */

/*!
 * @brief Constructs a new Game object.
 * @details Registers all necessary components, sets up initial entities (player and enemy), and adds systems to the registry.
 */
Game::Game()
    : window(sf::VideoMode(800, 600), "Rtype"), gameStarted(false), is_start(true), hasPlayers(true), menu() {
    // Register components
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Collidable>();
    registry.register_component<Projectile>();

    // Create a controllable entity
    Player player(registry, 50.0f, 50.0f);
    controllableEntity = player.getEntity();

    // Create a non-controllable entity
    Enemy enemy(registry, 375.0f, 275.0f);

    // Add systems
    registry.add_system<Position, Velocity>(position_system);
    registry.add_system<Velocity, Controllable, Position, Drawable, Collidable>(control_system);
    registry.add_system<Position, Velocity, Projectile, Drawable, Collidable>(projectile_system);

    if (!font.loadFromFile("../assets/font.otf")) {
        std::cerr << "Failed to load font 'assets/font.otf'" << std::endl;
        throw std::runtime_error("Failed to load font");
    }
}

/*!
 * @brief Starts the main game loop.
 * @details The loop processes events, updates game logic if the game is running, and renders the current state.
 */
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (gameStarted) {
            update();
        }
        render();
    }
}

/*!
 * @brief Processes input events such as window close and mouse clicks.
 */
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            handlePlayerInput(event.mouseButton.button, true);
        }
    }
}

/*!
 * @brief Updates game state by running systems and handling collisions.
 * @details This function updates all systems, checks for collisions, and manages game-over conditions.
 */
void Game::update() {
    registry.run_systems();

    // Check for collisions
    auto collisions = collision_system(registry, registry.get_components<Position>(), registry.get_components<Drawable>(), registry.get_components<Collidable>(), registry.get_components<Controllable>(), registry.get_components<Projectile>(), is_start);
    for (const auto& [entity1, entity2] : collisions) {
        if (registry.get_components<Controllable>()[entity1]) {
            registry.kill_entity(entity1);
        }
        if (registry.get_components<Controllable>()[entity2]) {
            registry.kill_entity(entity2);
        }
    }

    // Check if there are no more players
    hasPlayers = false;
    for (const auto& controllable : registry.get_components<Controllable>()) {
        if (controllable) {
            hasPlayers = true;
            break;
        }
    }
    if (!hasPlayers) {
        gameStarted = false;
        menu.setGameOver(true);
    }

    if (is_start) {
        is_start = false;
    }
}

/*!
 * @brief Renders the current game state.
 * @details Draws all game entities if the game is running or renders the menu otherwise.
 */
void Game::render() {
    window.clear();

    if (gameStarted) {
        draw_system(registry, window, registry.get_components<Position>(), registry.get_components<Drawable>());
    } else {
        menu.render(window);
    }

    window.display();
}

/*!
 * @brief Handles player input events such as mouse clicks.
 * @param button The mouse button that was pressed.
 * @param isPressed Whether the button is pressed or released.
 * @details Starts the game if the start button is clicked or shoots a bullet if the game is running.
 */
void Game::handlePlayerInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (menu.isStartButtonClicked(mousePos)) {
            gameStarted = true;
        } else if (gameStarted) {
            shoot();
        }
    }
}

/*!
 * @brief Creates a new bullet entity and sets its velocity.
 * @details Spawns a bullet at the player's position and assigns it a velocity.
 */
void Game::shoot() {
    auto& playerPos = registry.get_components<Position>()[controllableEntity];
    Bullet bullet(registry, playerPos->x + 50.0f, playerPos->y + 25.0f, 1.0f);
    auto bulletEntity = bullet.getEntity();
    registry.get_components<Velocity>()[bulletEntity] = Velocity{1.0f, 0.0f};
}
