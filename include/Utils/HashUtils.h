#pragma once
#include <utility>
#include <functional>

template<typename T, typename U>
struct pair_hash {
    std::size_t operator()(const std::pair<T, U>& p) const {
        return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
    }
};