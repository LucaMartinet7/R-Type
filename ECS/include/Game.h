/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Game
*/

#ifndef GAME_H
    #define GAME_H

#include <SFML/Graphics.hpp>
#include "Registry.h"
#include "Position.h"
#include "Velocity.h"
#include "Drawable.h"
#include "Controllable.h"
#include "Collidable.h"
#include "Projectile.h"
#include "PositionSystem.h"
#include "ControlSystem.h"
#include "DrawSystem.h"
#include "ProjectileSystem.h"
#include "CollisionSystem.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Mouse::Button button, bool isPressed);
    void createProjectile();

    Registry registry;
    sf::RenderWindow window;
    sf::Font font;
    sf::RectangleShape startButton;
    bool gameStarted;
    bool is_start;
    Registry::Entity controllableEntity;
};

#endif // GAME_H
