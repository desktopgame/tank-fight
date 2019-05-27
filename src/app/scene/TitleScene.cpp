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
      mModelManager(modelManager),
      camera() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto pos =
            Vector3(msize.x * 24 * 0.1f, msize.y * 0.1f, msize.z * 24 * 0.1f);
        camera.transform.position = pos;
}

void TitleScene::show() {}

void TitleScene::update() { camera.debugControl(); }

void TitleScene::draw() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        camera.beginDraw();
        for (int i = 0; i < 48; i++) {
                for (int j = 0; j < 48; j++) {
                        auto model = mModelManager->getModel(path);
                        auto pos =
                            Vector3(msize.x * i * 0.1f, 0, msize.z * j * 0.1f);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(0.1f, 0.1f, 0.1f);
                        model->draw();
                        ::glPopMatrix();
                }
        }
        for (int i = 0; i < 10; i++) {
        }
        camera.endDraw();
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame