#ifndef APP_MODEL_QUADRANGLE_HPP
#define APP_MODEL_QUADRANGLE_HPP
#include "UV.hpp"
#include "Vector3.hpp"
namespace gel {
struct Quadrangle {
        Quadrangle();
        Vector3 ver;
        Vector3 nor;
        UV uv;
};
}  // namespace gel
#endif