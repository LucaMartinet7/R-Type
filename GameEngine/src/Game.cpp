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
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 600), "Rtype"), gameStarted(false), is_start(true) {
    // Register components
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Collidable>();
    registry.register_component<Projectile>();

    // Create a controllable entity
    controllableEntity = registry.spawn_entity();
    registry.add_component<Position>(controllableEntity, {50.0f, 50.0f});
    registry.add_component<Velocity>(controllableEntity, {0.0f, 0.0f});
    registry.add_component<Drawable>(controllableEntity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Controllable>(controllableEntity, {});
    registry.add_component<Collidable>(controllableEntity, {true});

    // Create a non-controllable entity
    auto nonControllableEntity = registry.spawn_entity();
    registry.add_component<Position>(nonControllableEntity, {375.0f, 275.0f});
    registry.add_component<Drawable>(nonControllableEntity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Collidable>(nonControllableEntity, {true});

    // Add systems
    registry.add_system<Position, Velocity>(position_system);
    registry.add_system<Velocity, Controllable, Position, Drawable, Collidable>(control_system);
    registry.add_system<Position, Projectile, Drawable, Collidable>(projectile_system);

    if (!font.loadFromFile("../assets/font.otf")) {
        std::cerr << "Failed to load font 'assets/font.otf'" << std::endl;
        throw std::runtime_error("Failed to load font");
    }

    startButton.setSize(sf::Vector2f(200, 100));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300, 250);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (gameStarted) {
            update();
        }
        render();
    }
}

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
    if (is_start) {
        is_start = false;
    }
    }

void Game::render() {
    window.clear();

    if (gameStarted) {
        draw_system(registry, window, registry.get_components<Position>(), registry.get_components<Drawable>());
    } else {
        sf::Text text("Click to Start", font, 50);
        text.setFillColor(sf::Color::White);
        text.setPosition(250, 150);
        window.draw(text);
        window.draw(startButton);
    }

    window.display();
}

void Game::handlePlayerInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            gameStarted = true;
        } else if (gameStarted) {
            createProjectile();
        }
    }
}

void Game::createProjectile() {
    auto projectileEntity = registry.spawn_entity();
    auto& playerPos = registry.get_components<Position>()[controllableEntity];
    registry.add_component<Position>(projectileEntity, {playerPos->x + 50.0f, playerPos->y + 25.0f});
    registry.add_component<Projectile>(projectileEntity, {1.0f});
    registry.add_component<Drawable>(projectileEntity, {sf::RectangleShape(sf::Vector2f(5.0f, 5.0f))});
}
