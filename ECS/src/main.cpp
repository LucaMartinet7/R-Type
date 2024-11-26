//
// Created by noe on 26/11/2024.
//

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
    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Example");

    Registry registry;

    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();

    // Create a movable entity
    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, {100.0f, 100.0f});
    registry.add_component<Velocity>(entity, {0.0f, 0.0f});
    registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Controllable>(entity, {});

    // Create a static entity
    auto staticEntity = registry.spawn_entity();
    registry.add_component<Position>(staticEntity, {200.0f, 200.0f});
    registry.add_component<Drawable>(staticEntity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        control_system(registry);
        position_system(registry);

        window.clear();
        draw_system(registry, window);
        window.display();
    }

    return 0;
}