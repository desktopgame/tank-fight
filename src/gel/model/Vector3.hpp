#ifndef GEL_MODEL_VECTOR3_HPP
#define GEL_MODEL_VECTOR3_HPP
namespace gel {
/**
 * Vector3 is three dimensional vector.
 */
struct Vector3 {
        Vector3();
        Vector3(float x, float y, float z);
        float x;
        float y;
        float z;
        /**
         * @return
         */
        float length() const;
        /**
         * @return
         */
        Vector3& normalize();
        /**
         * @param v
         * @return
         */
        float dot(const Vector3& v) const;
        /**
         * @param v
         * @return
         */
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