/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Registry
*/

#ifndef REGISTRY_H
#define REGISTRY_H

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <vector>
#include <optional>
#include "SparseArray.hpp"
#include "Entity.hpp"
#include <tuple>

/*!
 * @class Registry
 * @brief Manages entities, components, and systems in the ECS (Entity Component System).
 * @details The Registry class handles the creation and destruction of entities,
 * the registration and management of components, and the execution of systems.
 */
class Registry {
public:
    using Entity = std::size_t;

    /*!
     * @brief Creates a new entity or reuses a previously killed one.
     * @return The ID of the newly spawned entity.
     */
    Entity spawn_entity() {
        if (!deadEntities.empty()) {
            Entity id = deadEntities.back();
            deadEntities.pop_back();
            return id;
        }
        return nextEntity++;
    }

    /*!
     * @brief Retrieves an entity from its index.
     * @param idx The index of the entity.
     * @return The entity corresponding to the index.
     */
    Entity entity_from_index(std::size_t idx) {
        return static_cast<Entity>(idx);
    }

    /*!
     * @brief Marks an entity as killed and removes its components.
     * @param e The entity to kill.
     */
    void kill_entity(Entity const& e) {
        for (auto& func : eraseFunctions) {
            func(*this, e);
        }
        deadEntities.push_back(e);
    }

    /*!
     * @brief Registers a new component type in the registry.
     * @tparam Component The type of the component to register.
     * @return A reference to the sparse array storing components of the given type.
     */
    template<typename Component>
    sparse_array<Component>& register_component() {
        auto typeIndex = std::type_index(typeid(Component));
        if (_componentArrays.find(typeIndex) == _componentArrays.end()) {
            _componentArrays[typeIndex] = sparse_array<Component>();
            eraseFunctions.push_back([](Registry& reg, Entity const& e) {
                reg.get_components<Component>().erase(e);
            });
        }
        return std::any_cast<sparse_array<Component>&>(_componentArrays[typeIndex]);
    }

    /*!
     * @brief Retrieves the sparse array of a specific component type.
     * @tparam Component The type of the component.
     * @return A reference to the sparse array storing components of the given type.
     */
    template <class Component>
    sparse_array<Component>& get_components() {
        auto typeIndex = std::type_index(typeid(Component));
        return std::any_cast<sparse_array<Component>&>(_componentArrays.at(typeIndex));
    }

    /*!
     * @brief Retrieves the sparse array of a specific component type (const version).
     * @tparam Component The type of the component.
     * @return A constant reference to the sparse array storing components of the given type.
     */
    template <class Component>
    const sparse_array<Component>& get_components() const {
        auto typeIndex = std::type_index(typeid(Component));
        return std::any_cast<const sparse_array<Component>&>(_componentArrays.at(typeIndex));
    }

    /*!
     * @brief Adds a component to an entity.
     * @tparam Component The type of the component.
     * @param to The entity to which the component is added.
     * @param c The component to add.
     * @return A reference to the added component.
     */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(Entity const& to, Component&& c) {
        return get_components<Component>().insert_at(to, std::forward<Component>(c));
    }

    /*!
     * @brief Emplaces a component on an entity.
     * @tparam Component The type of the component.
     * @tparam Params The types of the parameters for constructing the component.
     * @param to The entity to which the component is emplaced.
     * @param p The parameters for constructing the component.
     * @return A reference to the emplaced component.
     */
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(Entity const& to, Params&&... p) {
        return get_components<Component>().emplace_at(to, std::forward<Params>(p)...);
    }

    /*!
     * @brief Removes a component from an entity.
     * @tparam Component The type of the component.
     * @param from The entity from which the component is removed.
     */
    template <typename Component>
    void remove_component(Entity const& from) {
        get_components<Component>().erase(from);
    }

    /*!
     * @brief Adds a system to the registry.
     * @tparam Components The component types the system operates on.
     * @param f The function defining the system's behavior.
     */
    template <class... Components, typename Function>
    void add_system(Function&& f) {
        systems.emplace_back([this, f = std::forward<Function>(f)]() {
            f(*this, get_components<Components>()...);
        });
    }

    /*!
     * @brief Executes all registered systems.
     */
    void run_systems() {
        for (auto& system : systems) {
            system();
        }
    }

private:
    Entity nextEntity = 0; /*!< The next available entity ID. */
    std::vector<Entity> deadEntities; /*!< List of entities that have been killed and can be reused. */
    std::unordered_map<std::type_index, std::any> _componentArrays; /*!< Maps component types to their sparse arrays. */
    std::vector<std::function<void(Registry&, Entity const&)>> eraseFunctions; /*!< Functions to erase components of killed entities. */
    std::vector<std::function<void()>> systems; /*!< List of systems to execute. */
};

#endif // REGISTRY_H
