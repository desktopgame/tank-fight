#ifndef APP_DEVICE_FBXMODEL_HPP
#define APP_DEVICE_FBXMODEL_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "FbxMeshInfo.hpp"
#include "../model/Vector2.hpp"
#include "../model/Vector3.hpp"
#include "FbxMaterial.hpp"
#include "IModel.hpp"
#include "PngTexture.hpp"
#include "fbxsdk.h"
namespace gel {
class FbxModel : public IModel {
       public:
        FbxModel(FbxManager* fbxManager);
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        void draw() override;
        AABB getAABB() const override;

       private:
        void drawMeshInfo(FbxMeshInfo& meshInfo);
        void collectRecMesh(FbxNode* rootNode, std::vector<FbxMesh*>& dest);
        void collectMesh(FbxNode* rootNode, std::vector<FbxMesh*>& dest);
        FbxMesh* mapVertex(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxMesh* mapVertexIndex(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxMesh* mapNormal(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxMesh* mapUV(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxMesh* mapMaterial(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxMesh* mapSide(FbxMesh* fbxMesh, FbxMeshInfo& dest);
        FbxManager* fbxManager;
        FbxScene* fbxScene;
        FbxImporter* fbxImporter;
        std::vector<FbxMeshInfo> vinfo;
        AABB aabb;
};
}  // namespace gel
#endif