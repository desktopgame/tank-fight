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
        /**
         * return a (1, 1, 1)
         * @return
         */
        static Vector3 one();

        /**
         * @param a
         * @param b
         * @return
         */
        static float distance(const Vector3& a, const Vector3& b);

        /**
         * @param min
         * @param max
         * @return
         */
        Vector3 clamp(const Vector3& min, const Vector3& max) const;

        /**
         * @param min
         * @param max
         * @return
         */
        Vector3 clampXZ(const Vector3& min, const Vector3& max) const;

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