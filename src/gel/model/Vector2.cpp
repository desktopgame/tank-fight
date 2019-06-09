#include "Vector2.hpp"
#include <algorithm>
#include <cmath>
namespace gel {
Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::length() const { return std::sqrt(x * x + y * y); }

Vector2& Vector2::normalize() {
        float len = length();
        if (len != 0) {
                return *this /= len;
        }
        return *this;
}

float Vector2::dot(const Vector2& v) const { return x * v.x + y * v.y; }

Vector2 Vector2::one() { return Vector2(1, 1); }

float Vector2::distance(const Vector2& a, const Vector2& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return (float)::sqrt(dx * dx + dy * dy);
}

Vector2 Vector2::clamp(const Vector2& min, const Vector2& max) const {
        Vector2 v;
        v.x = std::min(max.x, std::max(min.x, x));
        v.y = std::min(max.y, std::max(min.y, y));
        return v;
}

Vector2 Vector2::operator-() const {
        Vector2 v;
        v.x = -x;
        v.y = -y;
        return v;
}

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
}  // namespace gel
