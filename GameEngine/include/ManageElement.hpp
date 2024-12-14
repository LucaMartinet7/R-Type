#ifndef MANAGEELEMENT_HPP_
#define MANAGEELEMENT_HPP_

// Standard libs
#include <iostream>
#include <memory>

// SFML
#include <SFML/Graphics.hpp>

// Local libs
#include "Object/IObject.hpp"
#include "Buttons.hpp"
#include "Icons.hpp"
#include "Background.hpp"
#include "Bullet.hpp"
#include "Input.hpp"
#include "Text.hpp"

#include "IEntity.hpp"
#include "Player.hpp"
#include "Obstacles.hpp"

class ManageElement {
  public:
    ManageElement();

    template <typename T, typename... Args> void createObject(Args &&... args) {
      std::shared_ptr<T> _new_object = std::make_shared<T>(args...);
      _list_object.push_back(_new_object);
    };

    template <typename T, typename... Args> void createEntity(Args &&... args) {
      std::shared_ptr<T> _new_entity = std::make_shared<T>(args...);
      _list_entity.push_back(_new_entity);
    };

    template <typename T, typename... Args> void createBullets(Args &&... args) {
      std::shared_ptr<T> _new_entity = std::make_shared<T>(args...);
      _list_bullets.push_back(_new_entity);
    };

    template <typename T, typename... Args> void createObstacles(Args &&... args) {
      std::shared_ptr<T> _new_entity = std::make_shared<T>(args...);
      _list_obstacles.push_back(_new_entity);
    };

    // Display
    void displayObjects(sf::RenderWindow &_window);
    void displayObjects(sf::RenderWindow &_window, sf::Shader &parallaxShader, float &offset, sf::Clock &clock);
    void displayEntities(sf::RenderWindow &_window);
    void displayObstacles(sf::RenderWindow &_window);
    void deleteObjects();

    // Getters
    std::vector<std::shared_ptr<IObject>> getListObject() {
      return _list_object;
    }
    std::vector<std::shared_ptr<IEntity>> getListObstacles() {
      return _list_obstacles;
    }

    std::shared_ptr<IObject> getIdObject(int id) {
      return _list_object[id];
    }
    std::shared_ptr<IEntity> getIdEntity(int id) {
      return _list_entity[id];
    }
    std::shared_ptr<IEntity> getIdObstacles(int id) {
      return _list_obstacles[id];
    }
    std::shared_ptr<IEntity> getIdBullets(int id) {
      return _list_bullets[id];
    }

    ~ManageElement();
  private:
    std::vector<std::shared_ptr<IObject>> _list_object;
    std::vector<std::shared_ptr<IEntity>> _list_entity;
    std::vector<std::shared_ptr<IEntity>> _list_obstacles;
    std::vector<std::shared_ptr<IEntity>> _list_bullets;
};

#endif /* MANAGESCENE_HPP_ */
