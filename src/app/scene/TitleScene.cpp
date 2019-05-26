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
        auto model = mModelManager->getModel("./assets/model/Block.fbx");
        auto aabb = model->getAABB();
        auto size = aabb.getSize();
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        glPushMatrix();
                        glTranslatef(size.x * i * 0.02f, 0, size.z * j * 0.02f);
                        glScalef(0.02f, 0.02f, 0.02f);
                        model->draw();
                        glColor3f(1.0f, 0, 0);
                        aabb.drawFrame();
                        glPopMatrix();
                }
        }
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame