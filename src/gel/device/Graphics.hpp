#ifndef GEL_DEVICE_GRAPHICS_HPP
#define GEL_DEVICE_GRAPHICS_HPP
#include <memory>
#include "../model/Color4.hpp"
#include "../model/Rect.hpp"
#include "../model/Vector2.hpp"
#include "../model/Vector3.hpp"
#include "IModel.hpp"
#include "ITexture.hpp"
namespace gel {

void drawTexture(const Vector2& position, const Color4& color,
                 const std::shared_ptr<ITexture>& texture);

void drawTexture(const Rect& dstRect, const Rect& srcRect, const Color4& color,
                 unsigned int tid);

void renderTexture(const Rect& dstRect, const Rect& srcRect,
                   const Color4& color, unsigned int tid);

void drawField(std::shared_ptr<IModel> model, Vector3 scale, int gridSize,
               int height);

void viewOrthoFixed(int width, int height);

void viewPerspective();
}  // namespace gel
#endif