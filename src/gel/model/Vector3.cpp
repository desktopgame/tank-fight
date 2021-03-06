#include "Vector3.hpp"
#include <cmath>
#include <algorithm>
namespace gel {
Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::length() const {
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

Vector3& Vector3::normalize() {
        float len = length();
        if (len != 0) {
                return *this /= len;
        }
        return *this;
}

float Vector3::dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const {
        return Vector3((y * v.z - z * v.y), (z * v.x - x * v.z),
                       (x * v.y - y * v.x));
}

Vector3 Vector3::one() { return Vector3(1, 1, 1); }

float Vector3::distance(const Vector3& a, const Vector3& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        float dz = a.z - b.z;
        return (float)::sqrt(dx * dx + dy * dy + dz * dz);
}

Vector3 Vector3::clamp(const Vector3& min, const Vector3& max) const {
        Vector3 v;
        v.x = std::min(max.x, std::max(min.x, x));
        v.y = std::min(max.y, std::max(min.y, y));
        v.z = std::min(max.z, std::max(min.z, z));
        return v;
}

Vector3 Vector3::clampXZ(const Vector3& min, const Vector3& max) const {
        Vector3 v = clamp(min, max);
        v.y = y;
        return v;
}

Vector3 Vector3::operator-() const {
        Vector3 v;
        v.x = -x;
        v.y = -y;
        v.z = -z;
        return v;
}

Vector3& Vector3::operator*=(float scale) {
        this->x *= scale;
        this->y *= scale;
        this->z *= scale;
        return *this;
}
Vector3& Vector3::operator/=(float scale) {
        this->x /= scale;
        this->y /= scale;
        this->z /= scale;
        return *this;
}
Vector3& Vector3::operator*=(const Vector3& a) {
        this->x *= a.x;
        this->y *= a.y;
        this->z *= a.z;
        return *this;
}
Vector3& Vector3::operator/=(const Vector3& a) {
        this->x /= a.x;
        this->y /= a.y;
        this->z /= a.z;
        return *this;
}
Vector3& Vector3::operator+=(const Vector3& a) {
        this->x += a.x;
        this->y += a.y;
        this->z += a.z;
        return *this;
}
Vector3& Vector3::operator-=(const Vector3& a) {
        this->x -= a.x;
        this->y -= a.y;
        this->z -= a.z;
        return *this;
}

Vector3 operator*(const Vector3& t1, const Vector3& t2) {
        return Vector3(t1) *= t2;
}
Vector3 operator/(const Vector3& t1, const Vector3& t2) {
        return Vector3(t1) /= t2;
}
Vector3 operator+(const Vector3& t1, const Vector3& t2) {
        return Vector3(t1) += t2;
}
Vector3 operator-(const Vector3& t1, const Vector3& t2) {
        return Vector3(t1) -= t2;
}

Vector3 operator*(const Vector3& t1, float scale) {
        return Vector3(t1) *= scale;
}
Vector3 operator*(float scale, const Vector3& t2) {
        return Vector3(t2) *= scale;
}
Vector3 operator/(const Vector3& t1, float scale) {
        return Vector3(t1) /= scale;
}
Vector3 operator/(float scale, const Vector3& t2) {
        return Vector3(t2) /= scale;
}
}  // namespace gel