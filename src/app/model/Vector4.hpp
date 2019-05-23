#ifndef APP_MODEL_VECTOR4_HPP
#define APP_MODEL_VECTOR4_HPP
namespace mygame {
struct Vector4 {
        Vector4();
        Vector4(float x, float y, float z, float w);
        float x;
        float y;
        float z;
        float w;
};
}  // namespace mygame
#endif