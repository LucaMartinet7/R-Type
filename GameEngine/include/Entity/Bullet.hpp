#ifndef BULLET_HPP_
#define BULLET_HPP_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "IEntity.hpp"
#include "Registry.hpp"
#include "components/Position.hpp"
#include "components/Projectile.hpp"
#include "components/Drawable.hpp"
#include "components/Collidable.hpp"

class Bullet : public IEntity {
public:
    Bullet(float x, float y, std::string asset, Registry& registry);

    virtual bool isPlayer() {
        return false;
    }

    virtual sf::Sprite getSprite() {
        return _bulletSprite;
    }

    virtual void setSpritePosition(float x, float y) {
        _bulletSprite.setPosition(x, y);
        auto& pos = registry.get_components<Position>()[bulletEntity];
        pos->x = x;
        pos->y = y;
    }

    virtual int getSourceRect() {
        return _sourceSprite.left;
    }

    virtual void setSourceRect(int rect) {
        _sourceSprite.left = rect;
    }

    virtual void updateTextureRect() {
        _bulletSprite.setTextureRect(_sourceSprite);
    }

    ~Bullet() {
        registry.kill_entity(bulletEntity);
    }

private:
    sf::IntRect _sourceSprite;
    sf::Texture _bulletText;
    sf::Sprite _bulletSprite;
    Registry& registry;
    Registry::Entity bulletEntity;
};

#endif // BULLET_HPP_
