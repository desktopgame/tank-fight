#ifndef APP_DEVICE_MODELMANAGER_HPP
#define APP_DEVICE_MODELMANAGER_HPP
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "fbxsdk.h"

namespace mygame {
class IModel;
class ModelManager {
       public:
        ModelManager();
        ~ModelManager();
        void addScene(const std::string& name);
        void removeScene(const std::string& name);

        void importFbx(const std::string& sceneName, const std::string& path);

       private:
        std::vector<std::shared_ptr<IModel> > models;
        std::unordered_map<std::string, FbxScene*> sceneMap;
        FbxManager* fbxManager;
};
}  // namespace mygame
#endif