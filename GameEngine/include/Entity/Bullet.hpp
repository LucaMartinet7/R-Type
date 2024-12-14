#ifndef BULLET_HPP_
#define BULLET_HPP_


#include <vector>
#include <iostream>

// Local libs
#include "IEntity.hpp"

class Bullet: public IEntity {
    public:
        Bullet(int x, int y, std::string asset);

        virtual bool isPlayer() {
          return false;
        }

        virtual sf::Sprite getSprite() {
          return _bulletSprite;
        }

        virtual void setSpritePosition(int x, int y) {
          _bulletSprite.setPosition(x, y);
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

        ~Bullet() = default;
    private:
      sf::IntRect _sourceSprite;
      sf::Texture _bulletText;
      sf::Sprite _bulletSprite;
};


void Game::createProjectile() {
    auto projectileEntity = registry.spawn_entity();
    auto& playerPos = registry.get_components<Position>()[controllableEntity];
    registry.add_component<Position>(projectileEntity, {playerPos->x + 50.0f, playerPos->y + 25.0f});
    registry.add_component<Projectile>(projectileEntity, {0.2f});
    registry.add_component<Drawable>(projectileEntity, {sf::RectangleShape(sf::Vector2f(5.0f, 5.0f))});
}




#endif
