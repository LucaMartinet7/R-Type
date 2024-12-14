#ifndef MENU_HPP_
#define MENU_HPP_

// Standard libs
#include <iostream>

// Local libs
#include "ILayer.hpp"

class Menu: public ILayer {
    public:
        Menu();

        virtual void initLayer();
        virtual void displayLayer(sf::RenderWindow &_window);
        virtual void deleteElements();
        virtual int manageEvent(sf::RenderWindow &_window);
        virtual void updateLayer(std::vector<std::string> _mapPlayer, std::vector<std::string> _mapObject, std::vector<std::string> _mapBullet, int _id) {};

        // Getters
        virtual bool exitButtonClicked() {
          return _exit;
        }
        virtual bool navNextButtonClicked() {
          return _next;
        }
        virtual bool navPrevButtonClicked() {
          return false;
        }
        virtual bool connectButtonClicked() {
          return false;
        }
        virtual bool joinButtonClicked() {
          return false;
        }
        virtual bool readyButtonClicked() {
          return false;
        }
        virtual std::string getHost() {
          return "";
        }
        virtual std::string getPort() {
          return "";
        }

        ~Menu() = default;
    private:
      ManageElement _manage_elem;

      // Events
      sf::Event Event;

      // Layer manager
      bool _exit = false;
      bool _next = false;
};

#endif /* MENU_HPP_ */
