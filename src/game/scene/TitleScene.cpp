#include "TitleScene.hpp"
TitleScene::TitleScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    const std::shared_ptr<gel::ModelManager>& modelManager)
    : textureManager(textureManager),
      modelManager(modelManager),
      finished(false) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { finished; }

void TitleScene::hide() {}
