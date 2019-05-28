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
        Transform transform;
};
}  // namespace gel
#endif