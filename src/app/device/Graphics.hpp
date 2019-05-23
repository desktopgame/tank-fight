#ifndef APP_DEVICE_GRAPHICS_HPP
#define APP_DEVICE_GRAPHICS_HPP
#include "../math/Vector2.hpp"
namespace mygame {
void drawTexture(Vector2 leftBottom, Vector2 leftTop, Vector2 rightTop,
                 Vector2 rightBottom, unsigned int tid);
}
#endif