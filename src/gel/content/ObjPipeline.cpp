#include "ObjPipeline.hpp"
#include "../device/ModelManager.hpp"
namespace gel {
ObjPipeline::ObjPipeline(const std::shared_ptr<ModelManager>& modelManager)
    : modelManager(modelManager) {}

bool ObjPipeline::accept(const std::string& path) { return true; }

void ObjPipeline::load(const std::string& path) {
	modelManager->loadObj(path);
}

void ObjPipeline::unload(const std::string& path) {
	modelManager->unload(path);
}
}  // namespace gel