#include "FbxModel.hpp"
#include <stdexcept>
namespace mygame {
FbxModel::FbxModel(FbxManager* fbxManager, FbxScene* fbxScene)
    : fbxManager(fbxManager), fbxScene(fbxScene) {}

void FbxModel::load(const std::string& path) {
        FbxImporter* importer = FbxImporter::Create(this->fbxManager, "");
        if (!importer->Initialize(path.c_str())) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        if (!importer->Import(fbxScene)) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
}

void FbxModel::unload(const std::string& path) {}
}  // namespace mygame