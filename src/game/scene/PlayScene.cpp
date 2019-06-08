#include "PlayScene.hpp"
#include "../../gel/ui/imgui/imgui_impl_glfw.h"
#include "../../gel/ui/imgui/imgui_impl_opengl2.h"

float PlayScene::BLOCK_SCALE = 0.1f;
float PlayScene::TANK_SCALE = 0.001f;
float PlayScene::BULLET_SCALE = 0.001f * 0.1f;
float PlayScene::BULLET_SPEED = 2;
float PlayScene::MOVE_SPEED = 0.009f;
float PlayScene::ROTATE_SPEED = 2.0f;
int PlayScene::PLAY_TIME = 100;

PlayScene::PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                     const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      camera(),
      spawners(),
      enemies(),
      spawnTimer(10),
      fireTimer(1),
      playTimer(1),
      playTime(PLAY_TIME),
      playTimeUI(
          textureManager,
          std::array<std::string, 10>{"./assets/image/number/0_W25x25.png",
                                      "./assets/image/number/1_W25x25.png",
                                      "./assets/image/number/2_W25x25.png",
                                      "./assets/image/number/3_W25x25.png",
                                      "./assets/image/number/4_W25x25.png",
                                      "./assets/image/number/5_W25x25.png",
                                      "./assets/image/number/6_W25x25.png",
                                      "./assets/image/number/7_W25x25.png",
                                      "./assets/image/number/8_W25x25.png",
                                      "./assets/image/number/9_W25x25.png"}),
      fired(false),
      bullets(),
      random() {
        this->blockAABBSize =
            mModelManager->getModel("./assets/model/Block.fbx")
                ->getAABB()
                .getSize();
        auto pos = gel::Vector3(blockAABBSize.x * 24 * BLOCK_SCALE,
                                blockAABBSize.y * BLOCK_SCALE * 2,
                                blockAABBSize.z * 24 * BLOCK_SCALE);
        camera.transform.position = pos;
        initSpawners(BLOCK_SCALE);
        spawn(5);
}

void PlayScene::show() {
        this->mFinished = false;
        this->playTime = PLAY_TIME;
}

void PlayScene::update() {
        for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->update();
        }
        for (int i = 0; i < bullets.size(); i++) {
                bullets[i]->update();
        }
        auto ec = actorToCache(std::vector<std::shared_ptr<Actor> >(
                                   enemies.begin(), enemies.end()),
                               TANK_SCALE);
        auto bc = actorToCache(std::vector<std::shared_ptr<Actor> >(
                                   bullets.begin(), bullets.end()),
                               BULLET_SCALE);
        for (int i = 0; i < ec.size(); i++) {
                auto eCache = ec[i];
                if (eCache.actor->isDestroyed()) {
                        continue;
                }
                auto ePos = eCache.actor->getPosition();
                for (int j = 0; j < bc.size(); j++) {
                        auto bCache = bc[j];
                        if (bCache.actor->isDestroyed()) {
                                continue;
                        }
                        auto bPos = bCache.actor->getPosition();
                        if (!(gel::Vector3::distance(ePos, bPos) < 1.0f)) {
                                continue;
                        }
                        /*
                        if (!gel::AABB::isIntersects(eCache.aabb,
                                                     bCache.aabb)) {
                                continue;
                        }
                        */
                        eCache.actor->destroy();
                        bCache.actor->destroy();
                }
        }
        remove_if(enemies);
        remove_if(bullets);
        movePlayer();
        fireBullet();
        checkPlayTime();
}

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
        for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->draw();
        }
        for (int i = 0; i < bullets.size(); i++) {
                bullets[i]->draw();
        }
        spawnTimer.update();
        if (spawnTimer.isElapsed()) {
                spawnTimer.reset();
                spawn(random.generate(1, 4));
        }
        camera.endDraw();
        drawIMGUI();
        playTimeUI.draw(playTime);
}

std::string PlayScene::getNextScene() const { return "title"; }

bool PlayScene::isFinished() const { return mFinished; }
void PlayScene::hide() { this->mFinished = false; }

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
                auto dir = gel::Vector3(0, 0, 1);
                spawners.push_back(std::make_shared<Spawner>(pos, rot, dir));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3(interval * i, baseY,
                                        (msize.x * blockScale) * 45);
                auto rot = gel::Vector3(0, 90, 0);
                auto dir = gel::Vector3(0, 0, -1);
                spawners.push_back(std::make_shared<Spawner>(pos, rot, dir));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 2, baseY,
                                        interval * i);
                auto rot = gel::Vector3(0, 0, 0);
                auto dir = gel::Vector3(1, 0, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot, dir));
        }
        for (int i = 1; i < 8; i++) {
                auto pos = gel::Vector3((msize.x * blockScale) * 45, baseY,
                                        interval * i);
                auto rot = gel::Vector3(0, 180, 0);
                auto dir = gel::Vector3(-1, 0, 0);
                spawners.push_back(std::make_shared<Spawner>(pos, rot, dir));
        }
}

void PlayScene::spawn() {
        auto iter = spawners.begin();
        auto end = spawners.end();
        while (iter != end) {
                auto v = *iter;
                if (v->isUsed()) {
                        break;
                }
                ++iter;
        }
        if (iter == end) {
                return;
        }
        while (enemies.size() < spawners.size()) {
                auto i = random.generate(0, spawners.size() - 1);
                if (spawners[i]->isUsed()) {
                        continue;
                }
                spawners[i]->use();
                auto enemy = std::make_shared<Enemy>(
                    mModelManager->getModel("./assets/model/Tank.fbx"),
                    spawners[i]->getPosition(), spawners[i]->getRotation(),
                    spawners[i]->getDirection());
                enemies.push_back(enemy);
                break;
        }
}

void PlayScene::spawn(int n) {
        if (n <= 0) {
                return;
        }
        while (n--) {
                spawn();
        }
}

void PlayScene::movePlayer() {
        auto mWindow = gel::Game::getInstance()->getWindow();
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
                camera.transform.rotation.x += ROTATE_SPEED;
        } else if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                camera.transform.rotation.x -= ROTATE_SPEED;
        }
        if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) {
                camera.transform.rotation.y += ROTATE_SPEED;
        } else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
                camera.transform.rotation.y -= ROTATE_SPEED;
        }
        if (glfwGetKey(mWindow, 'W') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.forward() *
                                             MOVE_SPEED;
        } else if (glfwGetKey(mWindow, 'S') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.backward() *
                                             MOVE_SPEED;
        }
        if (glfwGetKey(mWindow, 'A') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.left() *
                                             MOVE_SPEED;
        } else if (glfwGetKey(mWindow, 'D') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.right() *
                                             MOVE_SPEED;
        }
}

void PlayScene::fireBullet() {
        auto mWindow = gel::Game::getInstance()->getWindow();
        if (fired) {
                fireTimer.update();
                if (fireTimer.isElapsed()) {
                        this->fired = false;
                        fireTimer.reset();
                }
                return;
        }
        if (glfwGetKey(mWindow, 'Z') == GLFW_PRESS) {
                this->fired = true;
                auto bullet = newBullet();
                bullets.push_back(bullet);
        }
}

void PlayScene::checkPlayTime() {
        if (this->playTime == 0) {
                return;
        }
        playTimer.update();
        if (playTimer.isElapsed()) {
                playTimer.reset();
                this->playTime--;
        }
        if (this->playTime == 0) {
                this->mFinished = true;
        }
}

std::shared_ptr<Bullet> PlayScene::newBullet() {
        auto model = mModelManager->getModel("./assets/model/Ball.fbx");
        auto bullet = std::make_shared<Bullet>(
            model, camera.transform.position, camera.transform.rotation,
            gel::Vector3(1, 0, 1) * camera.transform.forward());
        bullet->setSpeed(BULLET_SPEED);
        return bullet;
}

void PlayScene::drawIMGUI() {}

std::vector<HitCache> PlayScene::actorToCache(
    const std::vector<std::shared_ptr<Actor> > actors, float scale) {
        std::vector<HitCache> v;
        for (int i = 0; i < actors.size(); i++) {
                auto act = actors[i];
                auto actAABB = act->getAABB();
                auto actMoveMat = gel::Matrix4();
                actMoveMat.setTranslate(act->getPosition());
                auto actScaleMat = gel::Matrix4();
                actScaleMat.setScale(gel::Vector3::one() * scale);
                auto actRotMat = gel::Matrix4();
                actRotMat.setRotateX(act->getRotation().x);
                actRotMat.setRotateY(act->getRotation().y);
                actRotMat.setRotateZ(act->getRotation().z);
                auto actRMoveMat = gel::Matrix4();
                actRMoveMat.setTranslate(-act->getPosition());
                auto actMat =
                    actMoveMat * actRotMat * actScaleMat * actRMoveMat;
                actAABB = actAABB.transform(actMat);
                v.push_back(HitCache(act, actAABB));
        }
        return v;
}