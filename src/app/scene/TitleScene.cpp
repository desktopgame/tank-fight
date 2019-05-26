#include "TitleScene.hpp"
#include "../device/FbxModel.hpp"
#include "../device/Graphics.hpp"
#include "../device/IModel.hpp"
#include "../device/ITexture.hpp"
#include "../device/ModelManager.hpp"
#include "../device/TextureManager.hpp"
#include "../gsystem/CharacterController.hpp"
#include "../gsystem/ModelRenderer.hpp"
#include "../gsystem/Runtime.hpp"
namespace mygame {

TitleScene::TitleScene(const std::shared_ptr<TextureManager>& textureManager,
                       const std::shared_ptr<ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      stage(Runtime::create("Stage")),
      camera(Runtime::create("Camera")) {
        camera->addComponent(std::make_shared<CharacterController>());
        auto path = "./assets/model/Block.fbx";
        auto msize = modelManager->getModel(path)->getAABB().getSize();
        for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 24; j++) {
                        auto obj = Runtime::create("Cell");
                        auto pos =
                            Vector3(msize.x * i * 0.1f, 0, msize.z * j * 0.1f);
                        auto modR =
                            std::make_shared<ModelRenderer>(path, modelManager);
                        obj->addComponent(modR);
                        obj->scale = Vector3(0.1f, 0.1f, 0.1f);
                        obj->position = pos;
                        stage->addChild(obj);
                }
        }
        camera->addChild(stage);
}

void TitleScene::show() {}

void TitleScene::update() { camera->onUpdate(); }

void TitleScene::draw() { camera->onDraw(); }

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame