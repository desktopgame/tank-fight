#include "ModelRenderer.hpp"
#include "../device/IModel.hpp"
namespace mygame {
ModelRenderer::ModelRenderer(const std::string& path,
                             const std::shared_ptr<ModelManager>& modelManager)
    : path(path), modelManager(modelManager) {}
void ModelRenderer::onUpdate(const std::shared_ptr<Object>& obj) {}
void ModelRenderer::onDraw(const std::shared_ptr<Object>& obj) {
	modelManager->getModel(path)->draw();
}
void ModelRenderer::onAwake(const std::shared_ptr<Object>& obj) {}
void ModelRenderer::onStart(const std::shared_ptr<Object>& obj) {}
}  // namespace mygame