#ifndef APP_MODEL_VECTOR3_HPP
#define APP_MODEL_VECTOR3_HPP
namespace mygame {
struct Vector3 {
        Vector3();
        Vector3(float x, float y, float z);
        float x;
        float y;
        float z;
        Vector3& operator*=(float scale);
        Vector3& operator/=(float scale);
        Vector3& operator*=(const Vector3& a);
        Vector3& operator/=(const Vector3& a);
        Vector3& operator+=(const Vector3& a);
        Vector3& operator-=(const Vector3& a);
};
Vector3 operator*(const Vector3& t1, const Vector3& t2);
Vector3 operator/(const Vector3& t1, const Vector3& t2);
Vector3 operator+(const Vector3& t1, const Vector3& t2);
Vector3 operator-(const Vector3& t1, const Vector3& t2);
Vector3 operator*(const Vector3& t1, float scale);
Vector3 operator*(float scale, const Vector3& t2);
Vector3 operator/(const Vector3& t1, float scale);
Vector3 operator/(float scale, const Vector3& t2);
}  // namespace mygame
#endif