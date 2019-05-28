#include "TitleScene.hpp"
#include "../device/FbxModel.hpp"
#include "../device/Graphics.hpp"
#include "../device/IModel.hpp"
#include "../device/ITexture.hpp"
#include "../device/ModelManager.hpp"
#include "../device/TextureManager.hpp"
namespace gel {

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
        auto gunPos = Vector3(msize.x * 12 * 0.1f, (msize.y * 0.1f * 3),
                              msize.z * 12 * 0.1f);
        camera.beginDraw();
        ::glPushMatrix();
        gel::drawField(mModelManager->getModel(path),
                          Vector3(0.1f, 0.1f, 0.1f), 48, 0);
        ::glPopMatrix();

        ::glPushMatrix();
        ::glTranslatef(gunPos.x, gunPos.y, gunPos.z);
        ::glScalef(0.001f, 0.001f, 0.001f);
        auto gunModel = mModelManager->getModel("./assets/model/Tank.fbx");
        gunModel->draw();
        ::glPopMatrix();
        camera.endDraw();
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace gel