#ifndef GEL_MODEL_VECTOR3_HPP
#define GEL_MODEL_VECTOR3_HPP
namespace gel {
struct Vector3 {
        Vector3();
        Vector3(float x, float y, float z);
        float x;
        float y;
        float z;
        float length() const;
        Vector3& normalize();
        float dot(const Vector3& v) const;
        Vector3 cross(const Vector3& v) const;
        Vector3 operator-() const;
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
}  // namespace gel
#endif