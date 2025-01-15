#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Registry.hpp"

class Player {
public:
    Player(Registry& registry, float x, float y);
    ~Player();
    void move(float x, float y);
    Registry::Entity getEntity() const;

private:
    Registry& registry;
    Registry::Entity entity;
};

#endif // PLAYER_HPP