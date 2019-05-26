#include "TitleScene.hpp"
#include "../device/FbxModel.hpp"
#include "../device/Graphics.hpp"
#include "../device/IModel.hpp"
#include "../device/ITexture.hpp"
#include "../device/ModelManager.hpp"
#include "../device/TextureManager.hpp"
#include "../gsystem/Runtime.hpp"
namespace mygame {

TitleScene::TitleScene(const std::shared_ptr<TextureManager>& textureManager,
                       const std::shared_ptr<ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      stage(Runtime::create("Stage")) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {
        auto model = mModelManager->getModel("./assets/model/Block.fbx");
        auto aabb = model->getAABB();
        auto size = aabb.getSize();
        auto scale = 0.1f;
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        glPushMatrix();
                        glTranslatef(size.x * i * scale, 0, size.z * j * scale);
                        glScalef(scale, scale, scale);
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