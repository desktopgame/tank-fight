#ifndef APP_MODEL_TRIANGLE_HPP
#define APP_MODEL_TRIANGLE_HPP
#include "UV.hpp"
#include "Vector3.hpp"
namespace mygame {
struct Triangle {
        Triangle();
        Vector3 ver;
        Vector3 nor;
        UV uv;
};
}  // namespace  mygame
#endif