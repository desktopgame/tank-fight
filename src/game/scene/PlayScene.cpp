#include "PlayScene.hpp"
#include "../../gel/ui/imgui/imgui_impl_glfw.h"
#include "../../gel/ui/imgui/imgui_impl_opengl2.h"

const float PlayScene::BLOCK_SCALE = 0.1f;
const float PlayScene::TANK_SCALE = 0.001f;
const float PlayScene::BULLET_SCALE = 0.001f * 0.1f;
const float PlayScene::BULLET_SPEED = 2;
const float PlayScene::MOVE_SPEED = 0.009f;
const float PlayScene::ROTATE_SPEED = 2.0f;
const int PlayScene::PLAY_TIME = 100;
const int PlayScene::STAGE_SIZE = 48;
const int PlayScene::STAGE_CENTER_X = 24;
const int PlayScene::STAGE_CENTER_Z = 24;
const int PlayScene::KILL_POINT = 100;
const int PlayScene::SPAWN_MIN = 1;
const int PlayScene::SPAWN_MAX = 4;

PlayScene::PlayScene(const std::shared_ptr<gel::GameDevice>& gameDevice,
                     PlayResult& playResult)
    : mFinished(false),
      mTextureManager(gameDevice->getTextureManager()),
      mModelManager(gameDevice->getModelManager()),
      audioManager(gameDevice->getAudioManager()),
      camera(),
      spawners(),
      enemies(),
      spawnTimer(10),
      fireTimer(1),
      playTimer(1),
      playTime(PLAY_TIME),
      playTimeUI(
          gameDevice->getTextureManager(),
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
      random(),
      skybox(),
      playResult(playResult),
      kill(0),
      bgmSrc(audioManager->getSource(
          "./assets/audio/bgm_maoudamashii_cyber44.wav")) {
        this->blockAABBSize =
            mModelManager->getModel("./assets/model/Block.fbx")
                ->getAABB()
                .getSize();
        auto pos = gel::Vector3(blockAABBSize.x * STAGE_CENTER_X * BLOCK_SCALE,
                                blockAABBSize.y * BLOCK_SCALE * 2,
                                blockAABBSize.z * STAGE_CENTER_Z * BLOCK_SCALE);
        skybox.position = pos;
        camera.transform.position = pos;
        this->stageMinX = 0.1f;
        this->stageMaxX = (46 * blockAABBSize.x * BLOCK_SCALE);
        this->stageMinZ = (-2 * blockAABBSize.z * BLOCK_SCALE);
        this->stageMaxZ = (46 * blockAABBSize.z * BLOCK_SCALE);
        initSkyBox();
        initSpawners(BLOCK_SCALE);
        spawn(5);
}

void PlayScene::show() {
        this->mFinished = false;
        this->playTime = PLAY_TIME;
        this->kill = 0;
        alSourcei(bgmSrc, AL_LOOPING, AL_TRUE);
        alSourcei(bgmSrc, AL_GAIN, 0.5f);
        alSourcePlay(bgmSrc);
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
                        if (!gel::AABB::isIntersects(eCache.aabb,
                                                     bCache.aabb)) {
                                continue;
                        }
                        kill += KILL_POINT;
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
        camera.beginDraw();
        glPushMatrix();
        skybox.draw(
            gel::Vector3(blockAABBSize.x * STAGE_CENTER_X * BLOCK_SCALE, 1,
                         blockAABBSize.z * STAGE_CENTER_Z * BLOCK_SCALE));
        gel::drawField(mModelManager->getModel(path),
                       gel::Vector3(BLOCK_SCALE, BLOCK_SCALE, BLOCK_SCALE),
                       STAGE_SIZE, 0);
        glPopMatrix();
        for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->draw();
        }
        for (int i = 0; i < bullets.size(); i++) {
                bullets[i]->draw();
        }
        spawnTimer.update();
        if (spawnTimer.isElapsed()) {
                spawnTimer.reset();
                spawn(random.generate(SPAWN_MIN, SPAWN_MAX));
        }
        camera.endDraw();
        drawIMGUI();
        drawTime();
#if DEBUG
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive,
                              ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

        ImGui::Begin("config 1");
        ImGui::Text("X %f", camera.transform.position.x);
        ImGui::Text("Y %f", camera.transform.position.y);
        ImGui::Text("Z %f", camera.transform.position.z);

        ImGui::End();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        gel::gui::render();
#endif
}

std::string PlayScene::getNextScene() const { return "result"; }

bool PlayScene::isFinished() const { return mFinished; }
void PlayScene::hide() {
        playResult.record(kill);
        this->mFinished = false;
        alSourceStop(bgmSrc);
}

// private
void PlayScene::initSkyBox() {
        auto negXTex =
            mTextureManager->getTexture("./assets/image/skybox/RIGHT.png");
        auto negYTex =
            mTextureManager->getTexture("./assets/image/skybox/BOTTOM.png");
        auto negZTex =
            mTextureManager->getTexture("./assets/image/skybox/FORWARD.png");
        auto posXTex =
            mTextureManager->getTexture("./assets/image/skybox/LEFT.png");
        auto posYTex =
            mTextureManager->getTexture("./assets/image/skybox/TOP.png");
        auto posZTex =
            mTextureManager->getTexture("./assets/image/skybox/BACK.png");
        skybox.posX = posXTex->getID();
        skybox.posY = posYTex->getID();
        skybox.posZ = posZTex->getID();
        skybox.negX = negXTex->getID();
        skybox.negY = negYTex->getID();
        skybox.negZ = negZTex->getID();
}

void PlayScene::initSpawners(float blockScale) {
        auto msize = mModelManager->getModel("./assets/model/Block.fbx")
                         ->getAABB()
                         .getSize();
        auto interval = (msize.x * blockScale) * ((float)STAGE_SIZE / 8.f);
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
        std::vector<bool> bitmap;
        for (int i = 0; i < spawners.size(); i++) bitmap.push_back(false);
        while (enemies.size() < spawners.size()) {
                auto i = random.generate(0, spawners.size() - 1);
                if (spawners[i]->isUsed()) {
                        bitmap[i] = true;
                        if (std::count(bitmap.begin(), bitmap.end(), true) ==
                            bitmap.size()) {
                                break;
                        }
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
        auto window = gel::Game::getInstance()->getWindow();
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                camera.transform.rotation.x += ROTATE_SPEED;
        } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                camera.transform.rotation.x -= ROTATE_SPEED;
        }
        if (glfwGetKey(window, 'W') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.forward() *
                                             MOVE_SPEED;
        } else if (glfwGetKey(window, 'S') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.backward() *
                                             MOVE_SPEED;
        }
        if (glfwGetKey(window, 'A') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.left() *
                                             MOVE_SPEED;
        } else if (glfwGetKey(window, 'D') == GLFW_PRESS) {
                camera.transform.position += gel::Vector3(1, 0, 1) *
                                             camera.transform.right() *
                                             MOVE_SPEED;
        }
        camera.transform.position = camera.transform.position.clampXZ(
            gel::Vector3(stageMinX, 0, stageMinZ),
            gel::Vector3(stageMaxX, 0, stageMaxZ));
}

void PlayScene::fireBullet() {
        auto window = gel::Game::getInstance()->getWindow();
        if (fired) {
                fireTimer.update();
                if (fireTimer.isElapsed()) {
                        this->fired = false;
                        fireTimer.reset();
                }
                return;
        }
        if (glfwGetKey(window, 'Z') == GLFW_PRESS) {
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
#if DEBUG
        auto window = gel::Game::getInstance()->getWindow();
        if (glfwGetKey(window, 'T') == GLFW_PRESS) {
                this->playTime = 10;
        }
#endif
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

void PlayScene::drawTime() {
        auto size = playTimeUI.calcSize(playTime);
        auto wsize = gel::Game::getInstance()->getWindowSize();
        auto npos = (wsize - size) / 2;
        npos.y = 0;
        playTimeUI.position = npos;
        playTimeUI.draw(playTime);
}

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
                auto actRotXMat = gel::Matrix4();
                auto actRotYMat = gel::Matrix4();
                auto actRotZMat = gel::Matrix4();
                actRotXMat.setRotateX(act->getRotation().x * (3.14f / 180.0f));
                actRotYMat.setRotateY(act->getRotation().y * (3.14f / 180.0f));
                actRotZMat.setRotateZ(act->getRotation().z * (3.14f / 180.0f));
                auto actRMoveMat = gel::Matrix4();
                actRMoveMat.setTranslate(-act->getPosition());
                auto modelMat = actScaleMat *
                                (actRotZMat * actRotXMat * actRotYMat) *
                                actMoveMat;
                actAABB = actAABB.transform(modelMat);
                v.push_back(HitCache(act, actAABB));
        }
        return v;
}