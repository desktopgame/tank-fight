#include "Rect.hpp"
namespace gel {
Rect::Rect(const Vector2& position, const Vector2& size)
    : position(position), size(size) {}

Rect::Rect(float x, float y, float w, float h) : position(x, y), size(w, h) {}
}  // namespace gel