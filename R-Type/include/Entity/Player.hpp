#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Drawable.hpp"
#include "components/Controllable.hpp"
#include "components/Collidable.hpp"

class Player {
public:
    Player(Registry& registry, float x, float y);
    void move(float x, float y);
    Registry::Entity getEntity() const;

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // PLAYER_HPP