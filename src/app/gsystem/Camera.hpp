#ifndef APP_GSYSTEM_CAMERA_HPP
#define APP_GSYSTEM_CAMERA_HPP
#include "Transform.hpp"
namespace mygame {
class Camera {
       public:
        Camera();
        void beginDraw() const;
        void endDraw() const;
        void debugControl();
        Transform transform;
};
}  // namespace mygame
#endif