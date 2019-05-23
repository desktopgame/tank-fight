#ifndef APP_DEVICE_FBXMODEL_HPP
#define APP_DEVICE_FBXMODEL_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "../math/Material.hpp"
#include "IModel.hpp"
#include "PngTexture.hpp"
#include "fbxsdk.h"
namespace mygame {
class FbxModel : public IModel {
       public:
        FbxModel(FbxManager* fbxManager);
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        void draw();

       private:
        FbxManager* fbxManager;
        FbxScene* fbxScene;
        FbxImporter* fbxImporter;
        std::vector<Material> materials;
        std::vector<std::shared_ptr<PngTexture> > textures;
        std::vector<GLuint> texNov;
};
}  // namespace mygame
#endif