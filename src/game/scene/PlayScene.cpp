#include "PlayScene.hpp"
#include "../../gel/ui/imgui/imgui_impl_glfw.h"
#include "../../gel/ui/imgui/imgui_impl_opengl2.h"

float PlayScene::BLOCK_SCALE = 0.1f;
float PlayScene::TANK_SCALE = 0.001f;
float PlayScene::BULLET_SCALE = 0.001f * 0.1f;
float PlayScene::MOVE_SPEED = 0.009f;
float PlayScene::ROTATE_SPEED = 2.0f;

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
      fired(false),
      bullets(),
      random() {
        this->blockAABBSize =
            mModelManager->getModel("./assets/model/Block.fbx")
                ->getAABB()
                .getSize();
        auto pos = gel::Vector3(blockAABBSize.x * 24 * BLOCK_SCALE,
                                blockAABBSize.y * BLOCK_SCALE,
                                blockAABBSize.z * 24 * BLOCK_SCALE);
        camera.transform.position = pos;
        initSpawners(BLOCK_SCALE);
        spawn(5);
}

void PlayScene::show() {}

void PlayScene::update() {
        for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->update();
        }
        for (int i = 0; i < bullets.size(); i++) {
                bullets[i]->update();
        }
        for(int i=0; i<bullets.size(); i++) {
                auto a = bullets[i];
        }
        remove_if(enemies);
        remove_if(bullets);
        movePlayer();
        fireBullet();
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

std::shared_ptr<Bullet> PlayScene::newBullet() {
        auto model = mModelManager->getModel("./assets/model/Ball.fbx");
        auto bullet = std::make_shared<Bullet>(
            model, camera.transform.position, camera.transform.rotation,
            gel::Vector3(1, 0, 1) * camera.transform.forward());
        return bullet;
}

void PlayScene::drawIMGUI() {}