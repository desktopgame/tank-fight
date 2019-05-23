#include "ModelManager.hpp"
#include <stdio.h>
#include <stdexcept>
#include "FbxModel.hpp"
namespace mygame {
ModelManager::ModelManager() : models(), sceneMap() {
        this->fbxManager = FbxManager::Create();
        if (this->fbxManager == NULL) {
                ::fprintf(stderr, "fatal error: FbxManager::Create()");
                ::abort();
        }
}

ModelManager::~ModelManager() { this->fbxManager->Destroy(); }

void ModelManager::addScene(const std::string& name) {
        if (sceneMap.count(name)) {
                throw std::logic_error("fatal error: ModelManager#addScene");
        }
        FbxScene* scene = FbxScene::Create(this->fbxManager, name.c_str());
        sceneMap[name] = scene;
}

void ModelManager::removeScene(const std::string& name) {
        if (sceneMap.count(name)) {
                FbxScene* scene = sceneMap[name];
                sceneMap.erase(name);
                scene->Destroy();
        }
}

void ModelManager::importFbx(const std::string& sceneName,
                             const std::string& path) {
        if (sceneMap.count(sceneName)) {
                throw std::logic_error("fatal error: ModelManager#importFbx");
        }
        auto scene = sceneMap[sceneName];
        auto fbxModel = std::make_shared<FbxModel>(this->fbxManager, scene);
        fbxModel->load(path);
}
}  // namespace mygame