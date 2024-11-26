//
// Created by noe on 26/11/2024.
//

#ifndef CONTROLSYSTEM_H
    #define CONTROLSYSTEM_H

#include "Registry.h"
#include "Velocity.h"
#include "Controllable.h"
#include <SFML/Window.hpp>

void control_system(Registry& registry) {
    auto& velocities = registry.get_components<Velocity>();
    auto& controllables = registry.get_components<Controllable>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto& vel = velocities[i];
        auto& ctrl = controllables[i];
        if (vel && ctrl) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                vel->vx = -1.0f;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                vel->vx = 1.0f;
            } else {
                vel->vx = 0.0f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                vel->vy = -1.0f;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                vel->vy = 1.0f;
            } else {
                vel->vy = 0.0f;
            }
        }
    }
}

#endif // CONTROLSYSTEM_H
