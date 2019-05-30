#include "TitleScene.hpp"
#include <glut.h>
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
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { finished; }

void TitleScene::hide() {}
