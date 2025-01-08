#ifndef BULLET_HPP
#define BULLET_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Projectile.hpp"
#include "components/Drawable.hpp"

class Bullet {
public:
    Bullet(Registry& registry, float x, float y, float speed);
    Registry::Entity getEntity() const;

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // BULLET_HPP