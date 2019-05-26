#include "Vector2.hpp"
#include <math.h>
namespace mygame {
Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2& Vector2::operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        return *this;
}
Vector2& Vector2::operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        return *this;
}
Vector2& Vector2::operator*=(const Vector2& a) {
        this->x *= a.x;
        this->y *= a.y;
        return *this;
}
Vector2& Vector2::operator/=(const Vector2& a) {
        this->x /= a.x;
        this->y /= a.y;
        return *this;
}
Vector2& Vector2::operator+=(const Vector2& a) {
        this->x += a.x;
        this->y += a.y;
        return *this;
}
Vector2& Vector2::operator-=(const Vector2& a) {
        this->x -= a.x;
        this->y -= a.y;
        return *this;
}

Vector2 operator*(const Vector2& t1, const Vector2& t2) {
        return Vector2(t1) *= t2;
}
Vector2 operator/(const Vector2& t1, const Vector2& t2) {
        return Vector2(t1) /= t2;
}
Vector2 operator+(const Vector2& t1, const Vector2& t2) {
        return Vector2(t1) += t2;
}
Vector2 operator-(const Vector2& t1, const Vector2& t2) {
        return Vector2(t1) -= t2;
}

Vector2 operator*(const Vector2& t1, float scale) {
        return Vector2(t1) *= scale;
}
Vector2 operator*(float scale, const Vector2& t2) {
        return Vector2(t2) *= scale;
}
Vector2 operator/(const Vector2& t1, float scale) {
        return Vector2(t1) /= scale;
}
Vector2 operator/(float scale, const Vector2& t2) {
        return Vector2(t2) /= scale;
}
}  // namespace mygame
