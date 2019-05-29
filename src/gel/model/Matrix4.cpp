#include "Matrix4.hpp"
#include <cmath>
namespace gel {

Matrix4::Matrix4() { reset(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); }

Matrix4::Matrix4(std::array<std::array<float, 4>, 4> m) : m(m) {}

Matrix4::Matrix4(float a1, float a2, float a3, float a4, float b1, float b2,
                 float b3, float b4, float c1, float c2, float c3, float c4,
                 float d1, float d2, float d3, float d4)
    : m() {
        reset(a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4);
}

Matrix4& Matrix4::setIdentity() {
        reset(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        return *this;
}

Matrix4& Matrix4::setScale(const Vector3& v) {
        reset(v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, 1);
        return *this;
}

Matrix4& Matrix4::setRotateX(float angle) {
        reset(1, 0, 0, 0, 0, std::cos(angle), std::sin(angle), 0, 0,
              -std::sin(angle), std::cos(angle), 0, 0, 0, 0, 1);
        return *this;
}

Matrix4& Matrix4::setRotateY(float angle) {
        reset(std::cos(angle), 0, -std::sin(angle), 0, 0, 1, 0, 0,
              std::sin(angle), 0, std::cos(angle), 0, 0, 0, 0, 1);
        return *this;
}

Matrix4& Matrix4::setRotateZ(float angle) {
        reset(std::cos(angle), std::sin(angle), 0, 0, -std::sin(angle),
              std::cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
        return *this;
}

Matrix4& Matrix4::setTranslate(const Vector3& v) {
        reset(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, v.x, v.y, v.z, 1);
        return *this;
}

Matrix4& Matrix4::setPerspective(float fov, float aspect, float near,
                                 float far) {
        float f = 1.0f / std::tan(fov / 2.0f);
        reset(f / aspect, 0, 0, 0, 0, f, 0, 0, 0, 0,
              (far + near) / (near - far), -1, 0, 0,
              (2 * far * near) / (near - far), 0);
        return *this;
}

Matrix4& Matrix4::setLookAt(const Vector3& eye, const Vector3& at,
                            const Vector3& up) {
        Vector3 e(eye - at);
        e.normalize();
        Vector3 v(up.cross(e));
        v.normalize();
        Vector3 u(e.cross(v));
        reset(v.x, u.x, e.x, 0, v.y, u.y, e.y, 0, v.z, u.z, e.z, 0,
              (-eye.dot(v)), (-eye.dot(u)), (-eye.dot(e)), 1);
        return *this;
}

Vector3 Matrix4::transform(const Vector3& v) const {
        float x = (v.x * m[0][0]) + (v.y * m[1][0]) + (v.z * m[2][0]) + m[3][0];
        float y = (v.x * m[0][1]) + (v.y * m[1][1]) + (v.z * m[2][1]) + m[3][1];
        float z = (v.x * m[0][2]) + (v.y * m[1][2]) + (v.z * m[2][2]) + m[3][2];
        float w = (v.x * m[0][3]) + (v.y * m[1][3]) + (v.z * m[2][3]) + m[3][3];
        return Vector3(x / w, y / w, z / w);
}

Vector3 Matrix4::transformNormal(const Vector3& v) const {
        float x = v.x;
        float y = v.y;
        float a = m[0][0];
        float b = m[0][1];
        float c = m[1][0];
        float d = m[1][1];
        float e = m[2][0];
        float f = m[2][1];
        return Vector3((a * x) + (c * y) + e, (x * b) + (y * d) + f, 1);
}

void Matrix4::reset(float a1, float a2, float a3, float a4, float b1, float b2,
                    float b3, float b4, float c1, float c2, float c3, float c4,
                    float d1, float d2, float d3, float d4) {
        float line0[4] = {a1, a2, a3, a4};
        for (int i = 0; i < 4; i++) {
                m[0][i] = line0[i];
        }
        float line1[4] = {b1, b2, b3, b4};
        for (int i = 0; i < 4; i++) {
                m[1][i] = line1[i];
        }
        float line2[4] = {c1, c2, c3, c4};
        for (int i = 0; i < 4; i++) {
                m[2][i] = line2[i];
        }
        float line3[4] = {d1, d2, d3, d4};
        for (int i = 0; i < 4; i++) {
                m[3][i] = line3[i];
        }
}

float* Matrix4::toPtr(float buf[16]) const {
        for (int i = 0; i < 16; i++) {
                std::array<float, 4> src = m[i / 4];
                int offset = i % 4;
                buf[i] = src[offset];
        }
        return buf;
}
Matrix4& Matrix4::operator*=(const Matrix4& m2) {
        auto ret = Matrix4::Multiply(*this, m2);
        this->m = ret;
        return *this;
}
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
        return Matrix4(Matrix4::Multiply(m1, m2));
}

const Vector3 operator*(const Vector3& v, const Matrix4& m) {
        return m.transform(v);
}
// private
std::array<std::array<float, 4>, 4> Matrix4::Multiply(const Matrix4& m1,
                                                      const Matrix4& m2) {
        std::array<std::array<float, 4>, 4> ret;
        int n = 4;
        int m = 4;
        int l = 4;
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        for (int k = 0; k < l; k++) {
                                ret[i][j] += m1.m[i][k] * m2.m[k][j];
                        }
                }
        }
        return ret;
}
}  // namespace gel