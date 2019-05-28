#ifndef GEL_MODEL_TRIANGLE_HPP
#define GEL_MODEL_TRIANGLE_HPP
#include "UV.hpp"
#include "Vector3.hpp"
namespace gel {
struct Triangle {
        Triangle();
        Vector3 ver;
        Vector3 nor;
        UV uv;
};
}  // namespace  gel
#endif