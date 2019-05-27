#include "Transform.hpp"
#include <cmath>
#define DEG2RAD (3.1415f / 180.0f)

namespace mygame {
Transform::Transform() : position(), scale(), angleX(), angleY(), angleZ() {}
Vector3 Transform::forward() const {
        auto ax = std::sin(angleX * DEG2RAD) * std::cos(angleY * DEG2RAD) * 1;
        auto ay = std::sin(angleY * DEG2RAD);
        auto az = std::cos(angleX * DEG2RAD) * std::cos(angleY * DEG2RAD) * 1;
        return Vector3(ax, ay, az);
}
Vector3 Transform::backward() const { return -forward(); }
Vector3 Transform::left() const { return -right(); }
Vector3 Transform::right() const {
        auto fwd = forward();
        return Vector3(-fwd.z, 0, fwd.x);
}
}  // namespace mygame