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

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Mouse::Button button, bool isPressed);
    void shoot();

    Registry registry;
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape startButton;
    bool gameStarted;
    bool is_start;
    bool hasPlayers;
    Registry::Entity controllableEntity;
    Menu menu;
};

#endif // GAME_H
