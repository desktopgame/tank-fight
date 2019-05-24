#ifndef APP_MODEL_MATERIAL_HPP
#define APP_MODEL_MATERIAL_HPP
#include <string>
#include <vector>
#include "Quadrangle.hpp"
#include "Reflection4.hpp"
#include "Triangle.hpp"
namespace mygame {
struct Material {
        Material();
        std::string name;
        Reflection4 color;
        float shininess;
        std::string texture;
        int textureNo;
        std::vector<Triangle> triangles;
        std::vector<Quadrangle> quads;
};
}  // namespace  mygame
#endif