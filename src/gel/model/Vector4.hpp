#ifndef GEL_MODEL_VECTOR4_HPP
#define GEL_MODEL_VECTOR4_HPP
namespace gel {
struct Vector4 {
        Vector4();
        Vector4(float x, float y, float z, float w);
        float x;
        float y;
        float z;
        float w;
};
}  // namespace gel
#endif