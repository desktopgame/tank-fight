#include "FbxModel.hpp"
#include <stdexcept>
namespace mygame {
FbxModel::FbxModel(FbxManager* fbxManager, FbxScene* fbxScene)
    : fbxManager(fbxManager), fbxScene(fbxScene) {}

void FbxModel::load(const std::string& path) {
        this->fbxImporter = FbxImporter::Create(this->fbxManager, "");
        if (!fbxImporter->Initialize(path.c_str())) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        if (!fbxImporter->Import(fbxScene)) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
}

void FbxModel::unload(const std::string& path) { fbxImporter->Destroy(); }
}  // namespace mygame