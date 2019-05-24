#ifndef APP_DEVICE_FBXMODEL_HPP
#define APP_DEVICE_FBXMODEL_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "FbxMaterial.hpp"
#include "../model/Vector2.hpp"
#include "../model/Vector3.hpp"
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
        FbxMesh* findRecMesh(FbxNode* rootNode);
        FbxMesh* findMesh(FbxNode* rootNode);
        FbxMesh* mapVertex(FbxMesh* fbxMesh);
        FbxMesh* mapVertexIndex(FbxMesh* fbxMesh);
        FbxMesh* mapNormal(FbxMesh* fbxMesh);
        FbxMesh* mapUV(FbxMesh* fbxMesh);
        FbxMesh* mapMaterial(FbxMesh* fbxMesh);
        FbxMesh* mapSide(FbxMesh* fbxMesh);
        FbxManager* fbxManager;
        FbxScene* fbxScene;
        FbxImporter* fbxImporter;
        std::vector<std::shared_ptr<PngTexture> > textures;
        std::vector<Vector3> vertex;
        std::vector<Vector3> normal;
        std::vector<FbxMaterial> materials;
        std::vector<UV> uv;
        std::vector<int> vertexIndex;
        std::vector<int> texId;
};
}  // namespace mygame
#endif