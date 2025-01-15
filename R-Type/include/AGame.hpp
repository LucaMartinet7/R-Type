/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** AGame
*/

#ifndef AGAME_HPP
#define AGAME_HPP

#include "IGame.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Registry.hpp"
#include "Boss.hpp"
#include "Registry.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Drawable.hpp"
#include "Controllable.hpp"
#include "Collidable.hpp"
#include "Projectile.hpp"
#include "PlayerAction.hpp"
#include <vector>

class AGame : public IGame {
    protected:
        std::vector<PlayerAction> playerActions; // Shared player action system
        std::vector<Player> players;
        std::vector<Enemy> enemies;
        std::vector<Bullet> bullets;
        std::vector<Boss> bosses;
        Registry registry;

    public:
        virtual ~AGame();

        // Implement player action management functions
        void addPlayerAction(int playerId, int actionId) override;
        void processPlayerActions() override;
        void deletePlayerAction() override;
        const std::vector<PlayerAction>& getPlayerActions() const override;

        //Getter functions for player, bullet and enemy positions for server to build package to send to client
        std::pair<float, float> getPlayerPosition(int playerId) const override;
        std::pair<float, float> getBulletPosition(int bulletId) const override;
        std::pair<float, float> getEnemyPosition(int enemyId) const override;
};

#endif // AGAME_HPP
