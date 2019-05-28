#ifndef GEL_DEVICE_OBJMODEL_HPP
#define GEL_DEVICE_OBJMODEL_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "IModel.hpp"
#include "ObjMaterial.hpp"
#include "PngTexture.hpp"
namespace gel {
class ObjModel : public IModel {
       public:
        ObjModel();
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        void draw() override;
        AABB getAABB() const override;

       private:
        static std::string trimLeft(const std::string& src);
        static std::vector<std::string> split(const std::string& src, char c);
        static float tofloat(const std::string& src);
        static int toint(const std::string& src);
        void loadMaterialFromFile(const std::string& dir, const char* path);
        static std::string pathToDir(const std::string& path);
        std::vector<ObjMaterial> materials;
        std::vector<std::shared_ptr<PngTexture> > textures;
        std::vector<GLuint> texId;
        AABB aabb;
};
}  // namespace gel
#endif