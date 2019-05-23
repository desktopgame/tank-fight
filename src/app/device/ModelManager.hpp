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

        void loadFbx(const std::string& path);
        void unload(const std::string& path);
        std::shared_ptr<IModel> getModel(const std::string& path) const;

       private:
        std::unordered_map<std::string, std::shared_ptr<IModel> > modelMap;
        FbxManager* fbxManager;
};
}  // namespace mygame
#endif