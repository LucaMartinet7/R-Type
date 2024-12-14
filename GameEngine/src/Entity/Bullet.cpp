#include "Bullet.hpp"

Bullet::Bullet(int x, int y, std::string asset) {
    if (!_bulletText.loadFromFile(asset)) {
      std::cout << "Error: Could not display Bullet !" << std::endl;
    }

    _bulletSprite.setTexture(_bulletText);
    _bulletSprite.setPosition(x, y);
}

virtual void bulletmove(int movement) {
        _bulletSprite.setPosition(x + movement, y);
}