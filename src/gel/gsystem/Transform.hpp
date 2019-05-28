#ifndef GEL_GSYSTEM_TRANSFORM_HPP
#define GEL_GSYSTEM_TRANSFORM_HPP
#include "../model/Vector3.hpp"
namespace gel {
struct Transform {
        Transform();
        Vector3 forward() const;
        Vector3 backward() const;
        Vector3 left() const;
        Vector3 right() const;

        Vector3 position;
        Vector3 scale;
        float angleX;
        float angleY;
        float angleZ;
};
}  // namespace gel
#endif