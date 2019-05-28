#ifndef GEL_MODEL_VECVector2OR2_HPP
#define GEL_MODEL_VECVector2OR2_HPP
namespace gel {
struct Vector2 {
        Vector2();
        Vector2(float x, float y);
        float x;
        float y;
        float length() const;
        Vector2& normalize();
        float dot(const Vector2& v) const;
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