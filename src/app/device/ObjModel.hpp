#ifndef APP_DEVICE_OBJMODEL_HPP
#define APP_DEVICE_OBJMODEL_HPP
#include <GLFW/glfw3.h>
#include <memory>
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

       private:
        void loadMaterialFromFile(const std::string& dir, const char* path);
        static std::string pathToDir(const std::string& path);
        std::vector<ObjMaterial> materials;
        std::vector<std::shared_ptr<PngTexture> > textures;
        std::vector<GLuint> texId;
};
}  // namespace mygame
#endif