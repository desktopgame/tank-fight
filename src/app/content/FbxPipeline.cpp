#include "FbxPipeline.hpp"
#include "../device/ModelManager.hpp"
namespace mygame {
FbxPipeline::FbxPipeline(const std::shared_ptr<ModelManager>& modelManager)
    : modelManager(modelManager) {}

bool FbxPipeline::accept(const std::string& path) { return true; }

void FbxPipeline::load(const std::string& path) { modelManager->loadFbx(path); }

void FbxPipeline::unload(const std::string& path) {
        modelManager->unload(path);
}
}  // namespace mygame