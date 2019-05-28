#include "Transform.hpp"
#include <cmath>
#define DEG2RAD (3.1415f / 180.0f)

namespace gel {
Transform::Transform() : position(), scale(), rotation() {}
Vector3 Transform::forward() const {
        auto ax =
            std::sin(rotation.x * DEG2RAD) * std::cos(rotation.y * DEG2RAD) * 1;
        auto ay = std::sin(rotation.y * DEG2RAD);
        auto az =
            std::cos(rotation.x * DEG2RAD) * std::cos(rotation.y * DEG2RAD) * 1;
        return Vector3(ax, ay, az);
}
Vector3 Transform::backward() const { return -forward(); }
Vector3 Transform::left() const { return -right(); }
Vector3 Transform::right() const {
        auto fwd = forward();
        return Vector3(-fwd.z, 0, fwd.x);
}
}  // namespace gel