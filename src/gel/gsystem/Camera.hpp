#ifndef GEL_GSYSTEM_CAMERA_HPP
#define GEL_GSYSTEM_CAMERA_HPP
#include "Transform.hpp"
namespace gel {
class Camera {
       public:
        Camera();
        void beginDraw() const;
        void endDraw() const;
        void debugControl();
        Vector3 getLook() const;
        Vector3 getUp() const;
        Transform transform;
};
}  // namespace gel
#endif