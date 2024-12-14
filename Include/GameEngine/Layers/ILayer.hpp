#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <vector>
#include <iostream>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ManageElement.hpp"
#include "TypeEnum.hpp"

class ILayer {
    public:
        virtual void initLayer() = 0;
        virtual void displayLayer(sf::RenderWindow &_window) = 0;
        virtual void deleteElements() = 0;
        virtual int manageEvent(sf::RenderWindow &_window) = 0;
        virtual void updateLayer(std::vector<std::string> _mapPlayer, std::vector<std::string> _mapObject, std::vector<std::string> _mapBullet, int _id) = 0;

        // Getters
        virtual bool exitButtonClicked() = 0;
        virtual bool navNextButtonClicked() = 0;
        virtual bool navPrevButtonClicked() = 0;
        virtual bool connectButtonClicked() = 0;
        virtual bool joinButtonClicked() = 0;
        virtual bool readyButtonClicked() = 0;
        virtual std::string getHost() = 0;
        virtual std::string getPort() = 0;

        virtual ~ILayer() = default;
};

#endif /* ISCENE_HPP_ */
