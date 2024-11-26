//
// Created by noe on 26/11/2024.
//

#ifndef DRAWSYSTEM_H
    #define DRAWSYSTEM_H

#include "Registry.h"
#include "Position.h"
#include "Drawable.h"
#include <SFML/Graphics.hpp>

void draw_system(Registry& registry, sf::RenderWindow& window) {
    auto& positions = registry.get_components<Position>();
    auto& drawables = registry.get_components<Drawable>();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto& pos = positions[i];
        auto& drawable = drawables[i];
        if (pos && drawable) {
            drawable->shape.setPosition(pos->x, pos->y);
            window.draw(drawable->shape);
        }
    }
}

#endif // DRAWSYSTEM_H
