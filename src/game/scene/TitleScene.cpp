#include "TitleScene.hpp"

TitleScene::TitleScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      camera() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto pos = gel::Vector3(msize.x * 24 * 0.1f, msize.y * 0.1f,
                                msize.z * 24 * 0.1f);
        camera.transform.position = pos;
}

void TitleScene::show() {}

void TitleScene::update() { camera.debugControl(); }

void TitleScene::draw() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto gunPos = gel::Vector3(msize.x * 12 * 0.1f, (msize.y * 0.1f * 3),
                                   msize.z * 12 * 0.1f);
        camera.beginDraw();
        ::glPushMatrix();
        gel::drawField(mModelManager->getModel(path),
                       gel::Vector3(0.1f, 0.1f, 0.1f), 48, 0);
        ::glPopMatrix();

        auto interval = (msize.x * 0.1f) * (48.f / 8.f);
        for (int i = 1; i < 8; i++) {
                ::glPushMatrix();
                ::glTranslatef(interval * i, gunPos.y, 0);
                ::glScalef(0.001f, 0.001f, 0.001f);
                auto gunModel =
                    mModelManager->getModel("./assets/model/Tank.fbx");
                gunModel->draw();
                ::glPopMatrix();
        }
        for (int i = 1; i < 8; i++) {
                ::glPushMatrix();
                ::glTranslatef(interval * i, gunPos.y, (msize.x * 0.1f) * 45);
                ::glScalef(0.001f, 0.001f, 0.001f);
                auto gunModel =
                    mModelManager->getModel("./assets/model/Tank.fbx");
                gunModel->draw();
                ::glPopMatrix();
        }
        for (int i = 1; i < 8; i++) {
                ::glPushMatrix();
                ::glTranslatef((msize.x * 0.1f) * 2, gunPos.y, interval * i);
                ::glScalef(0.001f, 0.001f, 0.001f);
                auto gunModel =
                    mModelManager->getModel("./assets/model/Tank.fbx");
                gunModel->draw();
                ::glPopMatrix();
        }
        for (int i = 1; i < 8; i++) {
                ::glPushMatrix();
                ::glTranslatef((msize.x * 0.1f) * 45, gunPos.y, interval * i);
                ::glScalef(0.001f, 0.001f, 0.001f);
                auto gunModel =
                    mModelManager->getModel("./assets/model/Tank.fbx");
                gunModel->draw();
                ::glPopMatrix();
        }
        camera.endDraw();
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
