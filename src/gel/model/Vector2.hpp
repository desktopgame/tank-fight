#ifndef GEL_MODEL_VECVector2OR2_HPP
#define GEL_MODEL_VECVector2OR2_HPP
namespace gel {
/**
 * Vector2 is two dimensional vector.
 */
struct Vector2 {
        Vector2();
        Vector2(float x, float y);
        float x;
        float y;
        /**
         * @return
         */
        float length() const;
        /**
         * @return
         */
        Vector2& normalize();
        /**
         * @param v
         * @return
         */
        float dot(const Vector2& v) const;

        /**
         * return (1, 1)
         * @return
         */
        static Vector2 one();

        Vector2 operator-() const;
        Vector2& operator*=(float scale);
        Vector2& operator/=(float scale);
        Vector2& operator*=(const Vector2& a);
        Vector2& operator/=(const Vector2& a);
        Vector2& operator+=(const Vector2& a);
        Vector2& operator-=(const Vector2& a);
};
Vector2 operator*(const Vector2& t1, const Vector2& t2);
Vector2 operator/(const Vector2& t1, const Vector2& t2);
Vector2 operator+(const Vector2& t1, const Vector2& t2);
Vector2 operator-(const Vector2& t1, const Vector2& t2);
Vector2 operator*(const Vector2& t1, float scale);
Vector2 operator*(float scale, const Vector2& t2);
Vector2 operator/(const Vector2& t1, float scale);
Vector2 operator/(float scale, const Vector2& t2);
}  // namespace gel
#endif