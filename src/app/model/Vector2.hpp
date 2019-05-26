#ifndef APP_MODEL_VECVector2OR2_HPP
#define APP_MODEL_VECVector2OR2_HPP
namespace mygame {
struct Vector2 {
        Vector2();
        Vector2(float x, float y);
        float x;
        float y;
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
}  // namespace mygame
#endif