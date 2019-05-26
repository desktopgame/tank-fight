#include "Vector3.hpp"
namespace mygame {
Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
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
}  // namespace mygame