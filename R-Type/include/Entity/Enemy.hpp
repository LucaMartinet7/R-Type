#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Registry.hpp"

class Enemy {
public:
    Enemy(Registry& registry, float x, float y);
    Registry::Entity getEntity() const;

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // ENEMY_HPP