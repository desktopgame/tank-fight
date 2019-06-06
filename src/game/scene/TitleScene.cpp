#include "TitleScene.hpp"
#include <glut.h>
#include "../../gel/device/Graphics.hpp"
TitleScene::TitleScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    const std::shared_ptr<gel::ModelManager>& modelManager)
    : textureManager(textureManager),
      modelManager(modelManager),
      finished(false),
      tankRotate(0) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {
        // gel::viewPerspective();
        ::glPushMatrix();
        ::gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

        ::glPushMatrix();
        ::glTranslatef(0.2, 0, -1);
        ::glRotatef(tankRotate, 0, 1, 0);
        ::glScalef(0.001f, 0.001f, 0.001f);
        modelManager->getModel("./assets/model/Tank.fbx")->draw();
        ::glPopMatrix();
        ::glPopMatrix();
        tankRotate += 0.02f;
        auto tex = textureManager->getTexture("./assets/image/Title.png");
        auto wsize = gel::Game::getInstance()->getWindowSize();
        auto centerPos = (wsize - tex->getSize()) / 2;
        centerPos.y = 0;
        gel::drawTexture(centerPos, tex);
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { finished; }

void TitleScene::hide() {}
