#include "PlayScene.hpp"
#include "../../gel/ui/imgui/imgui_impl_glfw.h"
#include "../../gel/ui/imgui/imgui_impl_opengl2.h"

float PlayScene::BLOCK_SCALE = 0.1f;
float PlayScene::TANK_SCALE = 0.001f;

PlayScene::PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                     const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      mTextureManager(textureManager),
      mModelManager(modelManager),
      camera(),
      spawners(),
      enemies(),
      timer(10),
      random() {
        auto path = "./assets/model/Block.fbx";
        auto msize = mModelManager->getModel(path)->getAABB().getSize();
        auto pos =
            gel::Vector3(msize.x * 24 * BLOCK_SCALE, msize.y * BLOCK_SCALE,
                         msize.z * 24 * BLOCK_SCALE);
        camera.transform.position = pos;
        initSpawners(BLOCK_SCALE);
        spawn(5);
}

void PlayScene::show() {}

void PlayScene::update() {
        for (int i = 0; i < enemies.size(); i++) {
                enemies[i]->update();
        }
        camera.debugControl();
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
        timer.update();
        if (timer.isElapsed()) {
                timer.reset();
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

void PlayScene::drawIMGUI() {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive,
                              ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 300), ImGuiSetCond_Once);

        ImGui::Begin("config 1");

        ImGui::End();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}