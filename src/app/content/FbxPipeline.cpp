#include "FbxPipeline.hpp"
#include "../device/ModelManager.hpp"
namespace mygame {
FbxPipeline::FbxPipeline(const std::shared_ptr<ModelManager>& modelManager,
                         const std::string& scene)
    : modelManager(modelManager), scene(scene) {}

FbxPipeline::FbxPipeline(const std::shared_ptr<ModelManager>& modelManager,
                         const char* scene)
    : modelManager(modelManager), scene(scene) {}

bool FbxPipeline::accept(const std::string& path) { return true; }

void FbxPipeline::load(const std::string& path) {
        modelManager->importFbx(scene, path);
}

void FbxPipeline::unload(const std::string& path) {}
}  // namespace mygame