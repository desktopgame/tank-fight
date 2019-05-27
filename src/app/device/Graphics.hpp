#ifndef APP_DEVICE_GRAPHICS_HPP
#define APP_DEVICE_GRAPHICS_HPP
#include <memory>
#include "../model/Vector2.hpp"
#include "../model/Vector3.hpp"
#include "IModel.hpp"
namespace mygame {
void drawTexture(Vector2 leftBottom, Vector2 leftTop, Vector2 rightTop,
                 Vector2 rightBottom, unsigned int tid);

void drawField(std::shared_ptr<IModel> model, Vector3 scale, int gridSize,
               int height);
}  // namespace mygame
#endif