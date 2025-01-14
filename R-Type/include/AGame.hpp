/*
** EPITECH PROJECT, 2025
** R-Type [WSL: Ubuntu]
** File description:
** AGame
*/

#ifndef AGAME_HPP
#define AGAME_HPP

#include "IGame.hpp"
#include <vector>
#include "PlayerAction.hpp"

class AGame : public IGame {
    protected:
        std::vector<PlayerAction> playerActions; // Shared player action system

    public:
        virtual ~AGame() = default;

        // Implement player action management functions
        void addPlayerAction(int playerId, int actionId) override;
        void processPlayerActions() override;
        void deletePlayerAction() override;
        const std::vector<PlayerAction>& getPlayerActions() const override;
};

#endif // AGAME_HPP
