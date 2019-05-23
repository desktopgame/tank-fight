#include "TitleScene.hpp"
#include "../device/Graphics.hpp"
#include "../device/ITexture.hpp"
#include "../device/TextureManager.hpp"
namespace mygame {

TitleScene::TitleScene(const std::shared_ptr<TextureManager>& textureManager)
    : mFinished(false), mTextureManager(textureManager) {}

void TitleScene::show() {}

void TitleScene::update() {}

void TitleScene::draw() {
        auto tid =
            mTextureManager->getTexture("./assets/image/sample.png")->getID();
        Vector2 leftTop(0, 0);
        Vector2 leftBottom(0, 240);
        Vector2 rightTop(320, 0);
        Vector2 rightBottom(320, 240);
        mygame::drawTexture(leftBottom, leftTop, rightTop, rightBottom, tid);
}

std::string TitleScene::getNextScene() const { return "play"; }

bool TitleScene::isFinished() const { return mFinished; }
void TitleScene::hide() {}
}  // namespace mygame