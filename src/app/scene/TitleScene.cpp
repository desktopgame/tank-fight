#include "TitleScene.hpp"
#include "../device/FbxModel.hpp"
#include "../device/Graphics.hpp"
#include "../device/IModel.hpp"
#include "../device/ITexture.hpp"
#include "../device/ModelManager.hpp"
#include "../device/TextureManager.hpp"
namespace mygame {

TitleScene::TitleScene(const std::shared_ptr<TextureManager>& textureManager,
                       const std::shared_ptr<ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {
        auto model = mModelManager->getModel("./assets/model/Gun1028.fbx");
        model->draw();
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame