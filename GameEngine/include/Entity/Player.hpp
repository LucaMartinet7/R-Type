#ifndef PLAYER_HPP_
#define PLAYER_HPP_

// Standard libs
#include <iostream>
#include <string>

// SFML
#include <SFML/Graphics.hpp>

// Local libs
#include "IEntity.hpp"
#include "components/Registry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Drawable.hpp"
#include "components/Controllable.hpp"
#include "components/Collidable.hpp"

class Player: public IEntity {
public:
    Player(Registry& registry, int x, int y, const std::string& asset);

    virtual bool isPlayer() override {
        return true;
    }

    virtual sf::Sprite getSprite() override {
        return _playerSprite;
    }

    virtual void setSpritePosition(int x, int y) override {
        _playerSprite.setPosition(x, y);
        auto& pos = registry.get_components<Position>()[playerEntity];
        if (pos) {
            pos->x = x;
            pos->y = y;
        }
    }

    virtual int getSourceRect() override {
        return _sourceSprite.left;
    }

    virtual void setSourceRect(int rect) override {
        _sourceSprite.left = rect;
        updateTextureRect();
    }

    virtual void updateTextureRect() override {
        _playerSprite.setTextureRect(_sourceSprite);
    }

    ~Player() = default;

private:
    Registry& registry;
    std::size_t playerEntity;
    sf::IntRect _sourceSprite;
    sf::Texture _playerText;
    sf::Sprite _playerSprite;
};

#endif // PLAYER_HPP_