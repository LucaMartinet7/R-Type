#include "ManageElement.hpp"

ManageLayer::ManageLayer() {

}

void ManageLayer::init() {

  // Add Menu to _list_layers
  std::shared_ptr<Menu> _menu = std::make_shared<Menu>();
  _list_layers.push_back(_menu);
  // Add lobby to _list_layers
  std::shared_ptr<Lobby> _lobby = std::make_shared<Lobby>();
  _list_layers.push_back(_lobby);
  // Add Game to _list_layers
  std::shared_ptr<Game> _game = std::make_shared<Game>();
  _list_layers.push_back(_game);
}

void ManageLayer::nextLayer() {
  // Delete assets
  _list_layers[_actual_index]->deleteElements();

  // Change actual layer by next layer in array
  _actual_index += 1;

  // Init next layer
  _list_layers[_actual_index]->initLayer();
}

void ManageLayer::prevLayer() {
  // Delete assets
  _list_layers[_actual_index]->deleteElements();

  // Change actual layer by prev layer in array
  _actual_index -= 1;

  // Init next layer
  _list_layers[_actual_index]->initLayer();
}


// ----------SFML---------

void ManageLayer::initWindow() {
  _window.create(sf::VideoMode(1920, 1080), "Spaceship action!", sf::Style::Default);
  _width = 1920;
  _height = 1080;
  _window.setFramerateLimit(60);
  _window.setVerticalSyncEnabled(true);
}

void ManageLayer::initMusic() {
    if (!_music.openFromFile("./Assets/musics/r-typemusic.ogg"))
        std::cout << "Error: Could not display _music !" << std::endl;
   
    _music.play();
}

void ManageLayer::renderLayer() {
  _window.clear();
  _list_layers[_actual_index]->displayLayer(_window);
  _window.display();
}

void ManageLayer::closeScreen() {
  _window.close();
}

ManageLayer::~ManageLayer() {

}
