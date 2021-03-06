#include "ModelDebugScene.hpp"
#include <glut.h>

ModelDebugScene::ModelDebugScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    const std::shared_ptr<gel::ModelManager>& modelManager)
    : mFinished(false),
      textureManager(textureManager),
      modelManager(modelManager),
      camera() {}
void ModelDebugScene::show() {}
void ModelDebugScene::update() {}

void ModelDebugScene::draw() {
        glPushMatrix();
        glLoadIdentity();
        auto scale = 0.1f;
        auto model = modelManager->getModel("./assets/model/TankCat.fbx");
        auto size = model->getAABB().getSize() * scale;
        gluLookAt(0, size.y, 0, 0, 0, 0, 0, 1, 0);
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(scale, scale, scale);
        model->draw();
        glPopMatrix();
        glPopMatrix();
}

bool ModelDebugScene::isFinished() const { return false; }
std::string ModelDebugScene::getNextScene() const { return "title"; }

void ModelDebugScene::hide() {}
