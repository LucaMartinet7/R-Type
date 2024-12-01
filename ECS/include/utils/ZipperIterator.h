#ifndef ZIPPER_ITERATOR_H
#define ZIPPER_ITERATOR_H

#include <tuple>
#include <iterator>
#include <optional>
#include <utility>

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

    zipper_iterator(iterator_tuple const& it_tuple, iterator_tuple const& end_tuple, size_t max)
        : _current(it_tuple), _end(end_tuple), _max(max), _idx(0) {
        // Ensure the iterator starts at a valid position
        if (!all_set(_seq)) {
            incr_all(_seq);
        }
    }

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
        while (_idx < _max && !all_set(_seq)) {
            (++std::get<Is>(_current), ...);
            ++_idx;
        }
    }

    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>) {
        return (... && (std::get<Is>(_current) != std::get<Is>(_end) && std::get<Is>(_current)->has_value()));
    }

    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>) {
        return std::tie(*std::get<Is>(_current)...);
    }

    iterator_tuple _current;
    iterator_tuple _end;
    size_t _max;
    size_t _idx;
    static constexpr std::index_sequence_for<Containers...> _seq{};
};

#endif // ZIPPER_ITERATOR_H