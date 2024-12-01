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
    Registry registry;

    // Register components
    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Drawable>();
    registry.register_component<Controllable>();

    // Create entities and add components
    auto entity = registry.spawn_entity();
    registry.add_component<Position>(entity, {0.0f, 0.0f});
    registry.add_component<Velocity>(entity, {0.0f, 0.0f});
    registry.add_component<Drawable>(entity, {sf::RectangleShape(sf::Vector2f(50.0f, 50.0f))});
    registry.add_component<Controllable>(entity, {});

    // Add systems
    registry.add_system<Position, Velocity>(position_system);
    registry.add_system<Velocity, Controllable>(control_system);

    sf::RenderWindow window(sf::VideoMode(800, 600), "ECS Example");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Run systems
        registry.run_systems();

        window.clear();
        draw_system(registry, window, registry.get_components<Position>(), registry.get_components<Drawable>());
        window.display();
    }

    return 0;
}