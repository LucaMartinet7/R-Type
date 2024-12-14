#ifndef OBSTACLES_HPP_
#define OBSTACLES_HPP_

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "IEntity.hpp"
#include "Registry.hpp"
#include "Position.hpp"
#include "Drawable.hpp"
#include "Collidable.hpp"

class Obstacles : public IEntity {
public:
    Obstacles(int x, int y, const std::string& asset, Registry& registry);

    virtual bool isPlayer() override {
        return false;
    }

    virtual sf::Sprite getSprite() override {
        return _obstaclesSprite;
    }

    virtual void setSpritePosition(int x, int y) override {
        _obstaclesSprite.setPosition(x, y);
        auto& pos = registry.get_components<Position>()[obstacleEntity];
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
        _obstaclesSprite.setTextureRect(_sourceSprite);
    }

    ~Obstacles() {
        registry.kill_entity(obstacleEntity);
    }

private:
    sf::IntRect _sourceSprite;
    sf::Texture _obstaclesText;
    sf::Sprite _obstaclesSprite;
    Registry& registry;
    Registry::Entity obstacleEntity;
};

#endif // OBSTACLES_HPP_