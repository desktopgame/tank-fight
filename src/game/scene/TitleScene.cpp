#include "TitleScene.hpp"
#include <glut.h>
#include "../../gel/device/Graphics.hpp"
TitleScene::TitleScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    const std::shared_ptr<gel::ModelManager>& modelManager)
    : textureManager(textureManager),
      modelManager(modelManager),
      finished(false),
      tankRotate(0),
      alphaDuration(1) {}

void TitleScene::show() { this->finished = false; }

void TitleScene::update() {
        if (glfwGetKey(gel::Game::getInstance()->getWindow(), GLFW_KEY_SPACE) ==
            GLFW_PRESS) {
                this->finished = true;
        }
}

void TitleScene::draw() {
        // gel::viewPerspective();
        gluLookAt(0.0, 0.1, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glPushMatrix();
        gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);

        glPushMatrix();
        glTranslatef(0.2, 0, -1);
        glRotatef(tankRotate, 0, 1, 0);
        glScalef(0.001f, 0.001f, 0.001f);
        modelManager->getModel("./assets/model/Tank.fbx")->draw();
        glPopMatrix();
        glPopMatrix();
        tankRotate += 0.02f;
        alphaDuration.update();
        float alpha = alphaDuration.progress();
        // draw `tank fight`
        auto tex = textureManager->getTexture("./assets/image/Title.png");
        auto wsize = gel::Game::getInstance()->getWindowSize();
        auto centerPos = (wsize - tex->getSize()) / 2;
        centerPos.y = 0;
        gel::drawTexture(centerPos, gel::Color4(1, 1, 1, 1), tex);
        // draw `start in space key`
        tex = textureManager->getTexture("./assets/image/StartInSpaceKey.png");
        centerPos = (wsize - tex->getSize()) / 2;
        centerPos.y = wsize.y - tex->getHeight();
        gel::drawTexture(centerPos, gel::Color4(1, 1, 1, alpha), tex);
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return finished; }

void TitleScene::hide() { this->finished = false; }
