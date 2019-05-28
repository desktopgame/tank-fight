#include "PlayScene.hpp"

float PlayScene::BLOCK_SCALE = 0.1f;
float PlayScene::TANK_SCALE = 0.001f;

PlayScene::PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                     const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      camera(),
      spawners(),
      timer(3) {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto pos =
            gel::Vector3(msize.x * 24 * BLOCK_SCALE, msize.y * BLOCK_SCALE,
                         msize.z * 24 * BLOCK_SCALE);
        camera.transform.position = pos;
        initSpawners(BLOCK_SCALE);
        spawn();
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
        auto tank = mModelManager->getModel("./assets/model/Tank.fbx");
        for (int i = 0; i < spawners.size(); i++) {
                auto spw = spawners[i];
                auto pos = spw->getPosition();
                auto rot = spw->getRotation();
                ::glPushMatrix();
                ::glTranslatef(pos.x, pos.y, pos.z);
                ::glRotatef(rot.y, 0, 1, 0);
                ::glRotatef(rot.x, 1, 0, 0);
                ::glRotatef(rot.z, 0, 0, 1);
                ::glScalef(TANK_SCALE, TANK_SCALE, TANK_SCALE);
                tank->draw();
                ::glPopMatrix();
        }
        timer.update();
        if (timer.isElapsed()) {
                timer.reset();
                // spawn();
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
                auto rot = gel::Vector3(0, 270, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3(interval * i, baseY,
                                        (msize.x * blockScale) * 45);
                auto rot = gel::Vector3(0, 90, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 2, baseY,
                                        interval * i);
                auto rot = gel::Vector3(0, 0, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 45, baseY,
                                        interval * i);
                auto rot = gel::Vector3(0, 180, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot));
        }
}

void PlayScene::spawn() {}