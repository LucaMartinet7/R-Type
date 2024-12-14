//
// Created by noe on 26/11/2024.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Registry.h"
#include "Position.h"
#include "Velocity.h"
#include "Drawable.h"
#include "Controllable.h"
#include "PositionSystem.h"
#include "ControlSystem.h"
#include "DrawSystem.h"

int main() {
    Registry registry;
    bool is_start = true;

    // Register components
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();
    registry.register_component<Collidable>();

    // Create a controllable entity
    auto controllableEntity = registry.spawn_entity();
    registry.add_component<Position>(controllableEntity, {50.0f, 50.0f}); // Set initial position to avoid collision
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Example");

    bool gameStarted = false;
    sf::Font font;
    if (!font.loadFromFile("../assets/font.otf")) {
        std::cerr << "Failed to load font 'assets/font.otf'" << std::endl;
        return -1;
    }

    sf::RectangleShape startButton(sf::Vector2f(200, 100));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        gameStarted = true;
                    }
                }
            }
        }
        window.clear();

        if (gameStarted) {
            // Run systems
            registry.run_systems();

            // Check for collisions
            auto collisions = collision_system(registry, registry.get_components<Position>(), registry.get_components<Drawable>(), registry.get_components<Collidable>(), registry.get_components<Controllable>(), is_start);
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

            draw_system(registry, window, registry.get_components<Position>(), registry.get_components<Drawable>());
        } else {
            // Display start menu
            sf::Text text("Click to Start", font, 50);
            text.setFillColor(sf::Color::White);
            text.setPosition(250, 150);
            window.draw(text);
            window.draw(startButton);
        }

        window.display();
    }

    return 0;
}