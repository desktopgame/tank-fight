#include "TitleScene.hpp"
#include "../device/Graphics.hpp"
#include "../device/TextureManager.hpp"
#include "../device/ITexture.hpp"
namespace mygame {

TitleScene::TitleScene(const std::shared_ptr<TextureManager>& textureManager)
    : mFinished(false), mTextureManager(textureManager) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {
        auto tid = mTextureManager->getTexture("./assets/image/sample.bmp")->getID();
        Vector2 leftTop(0, 0);
        Vector2 leftBottom(0, 100);
        Vector2 rightTop(100, 0);
        Vector2 rightBottom(100, 100);
        mygame::drawTexture(leftBottom, leftTop, rightTop, rightBottom, tid);
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame