#ifndef ZIPPER_H
#define ZIPPER_H

#include "ZipperIterator.h"

template <class... Containers>
class zipper {
public:
    using iterator = zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    zipper(Containers&... cs)
        : _begin(_compute_begin(cs...)), _end(_compute_end(cs...)), _size(_compute_size(cs...)) {}

    iterator begin() {
        return iterator(_begin, _end, _size);
    }

    iterator end() {
        return iterator(_end, _end, _size);
    }

private:
    static size_t _compute_size(Containers&... containers) {
        return std::min({containers.size()...});
    }

    static iterator_tuple _compute_begin(Containers&... containers) {
        return std::make_tuple(containers.begin()...);
    }

    static iterator_tuple _compute_end(Containers&... containers) {
        return std::make_tuple(containers.end()...);
    }

    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};

#endif // ZIPPER_H