//
// Created by noe on 26/11/2024.
//

#ifndef ENTITY_H
  #define ENTITY_H

class Entity {
  public:
    explicit Entity(std::size_t id) : id(id) {}
    operator std::size_t() const { return id; }
  private:
    std::size_t id;
};

#endif //ENTITY_H
