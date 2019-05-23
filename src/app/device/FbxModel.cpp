#include "FbxModel.hpp"
#include <stdexcept>
namespace mygame {
FbxModel::FbxModel(FbxManager* fbxManager)
    : fbxManager(fbxManager), fbxScene(nullptr) {}

void FbxModel::load(const std::string& path) {
        this->fbxScene = FbxScene::Create(this->fbxManager, "");
        this->fbxImporter = FbxImporter::Create(this->fbxManager, "");
        if (!fbxImporter->Initialize(path.c_str())) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        if (!fbxImporter->Import(fbxScene)) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
}

void FbxModel::unload(const std::string& path) {
        fbxImporter->Destroy();
        fbxScene->Destroy();
}

void FbxModel::draw() {}
}  // namespace mygame