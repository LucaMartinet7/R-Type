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

// ...existing code...

template <class... Containers>
class zipper_iterator {
    template <class Container>
    using iterator_t = decltype(std::declval<Container>().begin());
    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

public:
    using value_type = std::tuple<it_reference_t<Containers>...>;
    using reference = value_type;
    using pointer = void;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;

    zipper_iterator(iterator_tuple const& it_tuple, size_t max)
        : _current(it_tuple), _max(max), _idx(0) {}

    zipper_iterator(zipper_iterator const& z) = default;

    zipper_iterator& operator++() {
        incr_all(_seq);
        return *this;
    }

    zipper_iterator operator++(int) {
        zipper_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    value_type operator*() {
        return to_value(_seq);
    }

    value_type operator->() {
        return to_value(_seq);
    }

    friend bool operator==(zipper_iterator const& lhs, zipper_iterator const& rhs) {
        return lhs._current == rhs._current;
    }

    friend bool operator!=(zipper_iterator const& lhs, zipper_iterator const& rhs) {
        return !(lhs == rhs);
    }

private:
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>) {
        (++std::get<Is>(_current), ...);
        ++_idx;
        while (_idx < _max && !all_set(_seq)) {
            (++std::get<Is>(_current), ...);
            ++_idx;
        }
    }

    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>) {
        return (... && std::get<Is>(_current)->has_value());
    }

    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
        return std::tie(*std::get<Is>(_current)...);
    }

    iterator_tuple _current;
    size_t _max;
    size_t _idx;
    static constexpr auto _seq = std::index_sequence_for<Containers...>{};
};

template <class... Containers>
class zipper {
public:
    using iterator = zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    zipper(Containers&... cs)
        : _begin(std::make_tuple(cs.begin()...)), _end(_compute_end(cs...)), _size(_compute_size(cs...)) {}

    iterator begin() {
        return iterator(_begin, _size);
    }

    iterator end() {
        return iterator(_end, _size);
    }

private:
    static size_t _compute_size(Containers&... containers) {
        return std::min({containers.size()...});
    }

    static iterator_tuple _compute_end(Containers&... containers) {
        return std::make_tuple(containers.end()...);
    }

    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};

// ...existing code...

template <typename Component>
class sparse_array {
public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = const value_type&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    sparse_array() = default;
    sparse_array(const sparse_array& other) = default;
    sparse_array(sparse_array&& other) noexcept = default;
    ~sparse_array() = default;

    sparse_array& operator=(const sparse_array& other) = default;
    sparse_array& operator=(sparse_array&& other) noexcept = default;

    reference_type operator[](size_t idx) {
        if (idx >= _data.size()) {
            _data.resize(idx + 1);
        }
        return _data[idx];
    }

    const_reference_type operator[](size_t idx) const {
        return _data[idx];
    }

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    const_iterator cbegin() const { return _data.cbegin(); }
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    const_iterator cend() const { return _data.cend(); }

    size_type size() const { return _data.size(); }

    reference_type insert_at(size_type pos, const Component& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = component;
        return _data[pos];
    }

    reference_type insert_at(size_type pos, Component&& component) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos] = std::move(component);
        return _data[pos];
    }

    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... params) {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        _data[pos].emplace(std::forward<Params>(params)...);
        return _data[pos];
    }

    void erase(size_type pos) {
        if (pos < _data.size()) {
            _data[pos].reset();
        }
    }

    size_type get_index(const value_type& value) const {
        auto it = std::find(_data.begin(), _data.end(), value);
        if (it != _data.end()) {
            return std::distance(_data.begin(), it);
        }
        return static_cast<size_type>(-1);
    }

private:
    container_t _data;
};

#endif //SPARSEARRAY_H
