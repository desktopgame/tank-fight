#include "ModelManager.hpp"
#include <stdio.h>
#include <stdexcept>
#include "FbxModel.hpp"
#include "ObjModel.hpp"
namespace mygame {
ModelManager::ModelManager() : modelMap() {
        this->fbxManager = FbxManager::Create();
        if (this->fbxManager == NULL) {
                ::fprintf(stderr, "fatal error: FbxManager::Create()");
                ::abort();
        }
}

ModelManager::~ModelManager() { this->fbxManager->Destroy(); }

void ModelManager::loadFbx(const std::string& path) {
        auto fbxModel = std::make_shared<FbxModel>(this->fbxManager);
        fbxModel->load(path);
        modelMap[path] = fbxModel;
}

void ModelManager::loadObj(const std::string& path) {
        auto objModel = std::make_shared<ObjModel>();
        objModel->load(path);
        modelMap[path] = objModel;
}

void ModelManager::unload(const std::string& path) {
        if (modelMap.count(path)) {
                auto fbxModel = modelMap.at(path);
                modelMap.erase(path);
                fbxModel->unload(path);
        }
}

std::shared_ptr<IModel> ModelManager::getModel(const std::string& path) const {
        if (modelMap.count(path)) {
                return modelMap.at(path);
        }
        return nullptr;
}
}  // namespace mygame