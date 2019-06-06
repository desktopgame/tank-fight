#ifndef GEL_MODEL_RECT_HPP
#define GEL_MODEL_RECT_HPP
#include "Vector2.hpp"
namespace gel {
struct Rect {
        Vector2 position;
        Vector2 size;
        float left() const;
        float top() const;
        float right() const;
        float bottom() const;
        explicit Rect(const Vector2& position, const Vector2& size);
        explicit Rect(float x, float y, float w, float h);
};
}  // namespace gel
#endif