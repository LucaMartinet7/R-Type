#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Drawable.hpp"
#include "components/Collidable.hpp"

class Enemy {
public:
    Enemy(Registry& registry, float x, float y);
    Registry::Entity getEntity() const;

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // ENEMY_HPP