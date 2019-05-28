#ifndef APP_DEVICE_OBJMODEL_HPP
#define APP_DEVICE_OBJMODEL_HPP
#include <GLFW/glfw3.h>
#include <tiny_obj_loader.h>
#include <memory>
#include <set>
#include <vector>
#include "IModel.hpp"
#include "ObjMaterial.hpp"
#include "PngTexture.hpp"
namespace mygame {
class ObjModel : public IModel {
       public:
        ObjModel();
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        void draw() override;
        AABB getAABB() const override;

       private:
        std::vector<std::string> splitpath(const std::string& str,
                                           const std::set<char> delimiters);
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn;
        std::string error;
        AABB aabb;
};
}  // namespace mygame
#endif