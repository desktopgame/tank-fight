#ifndef APP_MODEL_COLOR4_HPP
#define APP_MODEL_COLOR4_HPP
namespace mygame {
struct Color4 {
        Color4();
        Color4(float r, float g, float b, float a);
        float r;
        float g;
        float b;
        float a;
};
}  // namespace mygame

#endif