#include "PlayScene.hpp"

float PlayScene::BLOCK_SCALE = 0.1f;
float PlayScene::TANK_SCALE = 0.001f;

PlayScene::PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                     const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      camera(),
      spawners() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto pos =
            gel::Vector3(msize.x * 24 * BLOCK_SCALE, msize.y * BLOCK_SCALE,
                         msize.z * 24 * BLOCK_SCALE);
        camera.transform.position = pos;
        initSpawners(BLOCK_SCALE);
}

void PlayScene::show() {}

void PlayScene::update() { camera.debugControl(); }

void PlayScene::draw() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto gunPos = gel::Vector3(msize.x * 12 * BLOCK_SCALE,
                                   (msize.y * BLOCK_SCALE * 3),
                                   msize.z * 12 * BLOCK_SCALE);
        camera.beginDraw();
        ::glPushMatrix();
        gel::drawField(mModelManager->getModel(path),
                       gel::Vector3(BLOCK_SCALE, BLOCK_SCALE, BLOCK_SCALE), 48,
                       0);
        ::glPopMatrix();
        auto tankModel = mModelManager->getModel("./assets/model/Tank.fbx");
        for (int i = 0; i < this->spawners.size(); i++) {
                auto spw = spawners[i];
                auto pos = spw->getPosition();
                ::glPushMatrix();
                ::glTranslatef(pos.x, pos.y, pos.z);
                ::glScalef(TANK_SCALE, TANK_SCALE, TANK_SCALE);
                tankModel->draw();
                ::glPopMatrix();
        }
        camera.endDraw();
}

std::string PlayScene::getNextScene() const { return "play"; }

bool PlayScene::isFinished() const { return mFinished; }
void PlayScene::hide() {}

// private
void PlayScene::initSpawners(float blockScale) {
        auto msize = mModelManager->getModel("./assets/model/Block.fbx")
                         ->getAABB()
                         .getSize();
        auto interval = (msize.x * blockScale) * (48.f / 8.f);
        auto baseY = (msize.y * blockScale * 3);
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3(interval * i, baseY, 0);
                spawners.push_back(std::make_shared<Spawner>(pos));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3(interval * i, baseY,
                                        (msize.x * blockScale) * 45);
                spawners.push_back(std::make_shared<Spawner>(pos));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 2, baseY,
                                        interval * i);
                spawners.push_back(std::make_shared<Spawner>(pos));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 45, baseY,
                                        interval * i);
                spawners.push_back(std::make_shared<Spawner>(pos));
        }
}