#include "Rect.hpp"
namespace gel {
Rect::Rect(const Vector2& position, const Vector2& size)
    : position(position), size(size) {}

Rect::Rect(float x, float y, float w, float h) : position(x, y), size(w, h) {}
float Rect::left() const { return position.x; }
float Rect::top() const { return position.y; }
float Rect::right() const { return position.x + size.x; }
float Rect::bottom() const { return position.y + size.y; }
}  // namespace gel