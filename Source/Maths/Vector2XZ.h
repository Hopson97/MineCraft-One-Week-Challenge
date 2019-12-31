#ifndef VECTOR2XZ_H_INCLUDED
#define VECTOR2XZ_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <functional>

struct VectorXZ {
    int x, z;
};

bool operator==(const VectorXZ &left, const VectorXZ &right) noexcept;

namespace std {
template <> struct hash<VectorXZ> {
    size_t operator()(const VectorXZ &vect) const noexcept
    {
        std::hash<decltype(vect.x)> hasher;

        auto hash1 = hasher(vect.x);
        auto hash2 = hasher(vect.z);

        return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
    }
};
} // namespace std

namespace std {
template <> struct hash<sf::Vector3i> {
    size_t operator()(const sf::Vector3i &vect) const noexcept
    {
        std::hash<decltype(vect.x)> hasher;

        auto hash1 = hasher(vect.x);
        auto hash2 = hasher(vect.y);
        auto hash3 = hasher(vect.z);

        return std::hash<decltype(vect.x)>{}(
            (hash1 ^ (hash2 << hash3) ^ hash3));
    }
};
} // namespace std

#endif // VECTOR2XZ_H_INCLUDED
