#include "ManageElement.hpp"

ManageElement::ManageElement() {

}

void ManageElement::displayObjects(sf::RenderWindow &_window) {
  for (auto &obj: _list_object) {
    if (obj->getType() == INPUT_HOST || obj->getType() == INPUT_PORT) {
      _window.draw(obj->getSprite());
      _window.draw(obj->getText());
    } else {
      _window.draw(obj->getSprite());
    }
  }
}

void ManageElement::displayObjects(sf::RenderWindow &_window, sf::Shader &parallaxShader, float &offset, sf::Clock &clock) {
  for(std::vector<std::shared_ptr<IObject>>::size_type i = 0; i != _list_object.size(); i++) {
    if (i == 0) {
      parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 10);
      _window.draw(_list_object[i]->getSprite(), &parallaxShader);
    }  else {
      _window.draw(_list_object[i]->getSprite());
    }
  }
}

void ManageElement::displayEntities(sf::RenderWindow &_window) {
  for (auto &entities: _list_entity) {
    _window.draw(entities->getSprite());
    if (entities->isPlayer())
      _window.draw(entities->getSprite());
  }
  for (auto &bullets: _list_bullets) {
    _window.draw(bullets->getSprite());
  }
}

void ManageElement::displayObstacles(sf::RenderWindow &_window) {
  for (auto &entities: _list_obstacles) {
    _window.draw(entities->getSprite());
  }
}

void ManageElement::deleteObjects() {
  for (auto &obj: _list_object) {
      obj->getSprite().setPosition(-2000, -2000);
  }
}

ManageElement::~ManageElement() {

}
