#ifndef GEL_MODEL_MATRIX4_HPP
#define GEL_MODEL_MATRIX4_HPP
#include <array>
#include "Vector3.hpp"
namespace gel {

struct Matrix4 {
        std::array<std::array<float, 4>, 4> m;
        Matrix4();
        Matrix4(std::array<std::array<float, 4>, 4> m);
        Matrix4(float a1, float a2, float a3, float a4, float b1, float b2,
                float b3, float b4, float c1, float c2, float c3, float c4,
                float d1, float d2, float d3, float d4);
        //単位行列の設定
        Matrix4& setIdentity();
        //拡大縮小行列の設定
        Matrix4& setScale(const Vector3& v);
        Matrix4& setRotateX(float angle);
        Matrix4& setRotateY(float angle);
        Matrix4& setRotateZ(float angle);
        //平行移動行列の設定
        Matrix4& setTranslate(const Vector3& v);
        Matrix4& setPerspective(float fov, float aspect, float near, float far);
        Matrix4& setLookAt(const Vector3& eye, const Vector3& at,
                           const Vector3& up);
        //座標変換
        Vector3 transform(const Vector3& v) const;
        //座標変換(回転のみ)
        Vector3 transformNormal(const Vector3& v) const;
        void reset(float a1, float a2, float a3, float a4, float b1, float b2,
                   float b3, float b4, float c1, float c2, float c3, float c4,
                   float d1, float d2, float d3, float d4);
        float* toPtr(float buf[16]) const;
        Matrix4& operator*=(const Matrix4& m2);
        static std::array<std::array<float, 4>, 4> Multiply(const Matrix4& m1,
                                                            const Matrix4& m2);
};
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
const Vector3 operator*(const Vector3& v, const Matrix4& m);
}  // namespace gel
#endif