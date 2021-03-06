#ifndef GEL_MODEL_FBXMATERIAL_HPP
#define GEL_MODEL_FBXMATERIAL_HPP
#include <string>
#include <vector>
#include "../model/Quadrangle.hpp"
#include "../model/Reflection4.hpp"
#include "../model/Triangle.hpp"
namespace gel {
struct FbxMaterial {
        FbxMaterial();
        std::string name;
        Reflection4 color;
        float shininess;
        std::string texture;
        int textureNo;
        std::vector<Triangle> triangles;
        std::vector<Quadrangle> quads;
};
}  // namespace  gel
#endif