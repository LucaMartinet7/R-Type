/*
** EPITECH PROJECT, 2024
** R-Type ECS
** File description:
** Sparse Array
*/

#ifndef SPARSEARRAY_H
    #define SPARSEARRAY_H

    #include <vector>
    #include <optional>
    #include <memory>
    #include <algorithm>

/*!
 * @class sparse_array
 * @brief A sparse array data structure for storing components in an ECS.
 * @details This template class provides an efficient way to store and access components
 * associated with entities, allowing for optional values and dynamic resizing.
 * @tparam Component The type of the component to store in the sparse array.
 */
template <typename Component>
class sparse_array {
public:
    using value_type = std::optional<Component>; /*!< Optional wrapper around the component type. */
    using reference_type = value_type&; /*!< Reference type for the component. */
    using const_reference_type = const value_type&; /*!< Constant reference type for the component. */
    using container_t = std::vector<value_type>; /*!< Internal container type for storing components. */
    using size_type = typename container_t::size_type; /*!< Size type for indexing. */
    using iterator = typename container_t::iterator; /*!< Iterator type for mutable access. */
    using const_iterator = typename container_t::const_iterator; /*!< Iterator type for constant access. */

    /*!
     * @brief Default constructor.
     */
    sparse_array() = default;

    /*!
     * @brief Copy constructor.
     * @param other The sparse array to copy from.
     */
    sparse_array(const sparse_array& other) = default;

    /*!
     * @brief Move constructor.
     * @param other The sparse array to move from.
     */
    sparse_array(sparse_array&& other) noexcept = default;

    /*!
     * @brief Destructor.
     */
    ~sparse_array() = default;

    /*!
     * @brief Copy assignment operator.
     * @param other The sparse array to copy from.
     * @return A reference to the current instance.
     */
    sparse_array& operator=(const sparse_array& other) = default;

    /*!
     * @brief Move assignment operator.
     * @param other The sparse array to move from.
     * @return A reference to the current instance.
     */
    sparse_array& operator=(sparse_array&& other) noexcept = default;

    /*!
     * @brief Access operator.
     * @param idx The index to access.
     * @return A reference to the optional component at the given index.
     */
    reference_type operator[](size_t idx) {
        if (idx >= _data.size()) {
            _data.resize(idx + 1);
        }
        return _data[idx];
    }

    /*!
     * @brief Const access operator.
     * @param idx The index to access.
     * @return A constant reference to the optional component at the given index.
     */
    const_reference_type operator[](size_t idx) const {
        return _data[idx];
    }

    /*!
     * @brief Returns an iterator to the beginning of the sparse array.
     */
    iterator begin() { return _data.begin(); }

    /*!
     * @brief Returns a constant iterator to the beginning of the sparse array.
     */
    const_iterator begin() const { return _data.begin(); }

    /*!
     * @brief Returns a constant iterator to the beginning of the sparse array.
     */
    const_iterator cbegin() const { return _data.cbegin(); }

    /*!
     * @brief Returns an iterator to the end of the sparse array.
     */
    iterator end() { return _data.end(); }

    /*!
     * @brief Returns a constant iterator to the end of the sparse array.
     */
    const_iterator end() const { return _data.end(); }

    /*!
     * @brief Returns a constant iterator to the end of the sparse array.
     */
    const_iterator cend() const { return _data.cend(); }

    /*!
     * @brief Returns the size of the sparse array.
     * @return The number of elements in the sparse array.
     */
    size_type size() const { return _data.size(); }

    /*!
     * @brief Inserts a component at the specified position.
     * @param pos The position at which to insert.
     * @param component The component to insert.
     * @return A reference to the inserted component.
     */
    reference_type insert_at(size_type pos, const Component& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = component;
        return _data[pos];
    }

    /*!
     * @brief Inserts a component at the specified position using move semantics.
     * @param pos The position at which to insert.
     * @param component The component to insert.
     * @return A reference to the inserted component.
     */
    reference_type insert_at(size_type pos, Component&& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = std::move(component);
        return _data[pos];
    }

    /*!
     * @brief Constructs a component in-place at the specified position.
     * @param pos The position at which to emplace the component.
     * @param params The parameters to construct the component.
     * @return A reference to the emplaced component.
     */
    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos].emplace(std::forward<Params>(params)...);
        return _data[pos];
    }

    /*!
     * @brief Removes a component at the specified position.
     * @param pos The position of the component to remove.
     */
    void erase(size_type pos) {
        if (pos < _data.size()) {
            _data[pos].reset();
        }
    }

    /*!
     * @brief Retrieves the index of a specific component.
     * @param value The component to find.
     * @return The index of the component or -1 if not found.
     */
    size_type get_index(const value_type& value) const {
        auto it = std::find(_data.begin(), _data.end(), value);
        if (it != _data.end()) {
            return std::distance(_data.begin(), it);
        }
        return -1;
    }

private:
    container_t _data; /*!< Internal container storing optional components. */
};

#endif //SPARSEARRAY_H
