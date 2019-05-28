#ifndef GEL_DEVICE_OBJMATERIAL_HPP
#define GEL_DEVICE_OBJMATERIAL_HPP

#include <string>
#include <vector>
#include "../model/Quadrangle.hpp"
#include "../model/Reflection4.hpp"
#include "../model/Triangle.hpp"
namespace gel {
struct ObjMaterial {
        ObjMaterial();
        std::string name;
        Reflection4 color;
        float shininess;
        std::string texture;
        int textureNo;
        std::vector<Triangle> triangles;
        std::vector<Quadrangle> quads;
        std::vector<unsigned int> triVerId;
        std::vector<unsigned int> triNorId;
        std::vector<unsigned int> triUVId;
        std::vector<unsigned int> quadVerId;
        std::vector<unsigned int> quadNorId;
        std::vector<unsigned int> quadUVId;
};
}  // namespace gel
#endif