#include "Bullet.hpp"

Bullet::Bullet(float x, float y, std::string asset, Registry& registry) : registry(registry) {
        if (!_bulletText.loadFromFile(asset)) {
            std::cout << "Error: Could not display Bullet!" << std::endl;
        }

        _bulletSprite.setTexture(_bulletText);
        _bulletSprite.setPosition(x, y);

        // Add to ECS registry
        bulletEntity = registry.spawn_entity();
        registry.add_component<Position>(bulletEntity, {x, y});
        registry.add_component<Projectile>(bulletEntity, {0.2f});
        registry.add_component<Drawable>(bulletEntity, Drawable{_bulletSprite});
        registry.add_component<Collidable>(bulletEntity, {true});
    }
