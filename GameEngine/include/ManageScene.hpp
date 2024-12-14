#ifndef MANAGESCENE_HPP_
#define MANAGESCENE_HPP_

// Standard libs
#include <iostream>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Local libs
#include "ILayer.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"
#include "Game.hpp"

class ManageLayer {
  public:
    ManageLayer();

    // Layers management
    void init();
    void nextLayer();
    void prevLayer();

    // SFML
    void initWindow();
    void initMusic();
    void renderLayer();
    void closeScreen();

    // Getters
    std::vector<std::shared_ptr<ILayer>> getListLayer() {
      return _list_layers;
    }
    std::shared_ptr<ILayer> getActualLayer() {
      return _list_layers[_actual_index];
    }
    bool windowsIsOpen() {
      return _window.isOpen();
    }
    sf::RenderWindow &getDisplayWindow() {
      return _window;
    }
    int getWidthSize() {
      return _width;
    }
    int getHeightSize() {
      return _height;
    }
    std::string getAssetsSize() {
      return _assets_size;
    }

    ~ManageLayer();
  private:
    int _actual_index = 0;
    std::vector<std::shared_ptr<ILayer>> _list_layers;

    // Window
    sf::RenderWindow _window;
    int _width = 0;
    int _height = 0;
    std::string _assets_size;

    // Audio
    sf::Music _music;
};

#endif /* MANAGESCENE_HPP_ */
