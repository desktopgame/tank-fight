#include "TitleScene.hpp"
namespace mygame {

TitleScene::TitleScene() : mFinished(false) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame