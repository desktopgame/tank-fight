#include "ResultScene.hpp"
ResultScene::ResultScene(
    const std::shared_ptr<gel::TextureManager>& textureManager,
    PlayResult& playResult)
    : textureManager(textureManager),
      playResult(playResult),
      finished(false),
      yourScoreTimer(2),
      isTimer(1),
      scoreTimer(1),
      returnTimer(1),
      transTimer(0.5f),
      transStart(false),
      phase(0),
      scoreNum(
          textureManager,
          std::array<std::string, 10>{"./assets/image/number/0_R50x50.png",
                                      "./assets/image/number/1_R50x50.png",
                                      "./assets/image/number/2_R50x50.png",
                                      "./assets/image/number/3_R50x50.png",
                                      "./assets/image/number/4_R50x50.png",
                                      "./assets/image/number/5_R50x50.png",
                                      "./assets/image/number/6_R50x50.png",
                                      "./assets/image/number/7_R50x50.png",
                                      "./assets/image/number/8_R50x50.png",
                                      "./assets/image/number/9_R50x50.png"}),
      alphaDuration(1) {}
void ResultScene::show() {
        this->phase = 0;
        this->transStart = false;
}
void ResultScene::update() {
        if (phase == 0) {
                yourScoreTimer.update();
                if (yourScoreTimer.isElapsed()) {
                        yourScoreTimer.reset();
                        this->phase = 1;
                }
        } else if (phase == 1) {
                isTimer.update();
                if (isTimer.isElapsed()) {
                        isTimer.reset();
                        this->phase = 2;
                }
        } else if (phase == 2) {
                scoreTimer.update();
                if (scoreTimer.isElapsed()) {
                        scoreTimer.reset();
                        this->phase = 3;
                }
        } else if (phase == 3) {
                returnTimer.update();
                if (returnTimer.isElapsed()) {
                        returnTimer.reset();
                        this->phase = 4;
                }
        }
        checkSpaceKey();
        alphaDuration.update();
}
void ResultScene::draw() {
        auto tex = textureManager->getTexture("./assets/image/TimeOver.png");
        auto size = tex->getSize();
        auto wsize = gel::Game::getInstance()->getWindowSize();
        auto centerPos = (wsize - size) / 2;
        centerPos.y = 0;
        gel::drawTexture(centerPos, gel::Color4(1, 1, 1, 1), tex);
        // draw `your score`
        if (phase >= 1) {
                tex =
                    textureManager->getTexture("./assets/image/YourScore.png");
                size = tex->getSize();
                centerPos.y = size.y + 20;
                gel::drawTexture(centerPos, gel::Color4(1, 1, 1, 1), tex);
        }
        if (phase >= 2) {
                tex = textureManager->getTexture("./assets/image/Is.png");
                size = tex->getSize();
                auto centerPos2 = (wsize - size) / 2;
                centerPos2.y = centerPos.y + size.y;
                centerPos = centerPos2;
                gel::drawTexture(centerPos2, gel::Color4(1, 1, 1, 1), tex);
        }
        if (phase >= 3) {
                size = scoreNum.calcSize(playResult.getCurrentScore());
                centerPos = (wsize - size) / 2;
                scoreNum.position = centerPos;
                scoreNum.draw(playResult.getCurrentScore());
        }
        if (phase >= 4) {
                tex = textureManager->getTexture(
                    "./assets/image/ReturnToTitleBySpaceKey.png");
                size = tex->getSize();
                centerPos = (wsize - size) / 2;
                centerPos.y =
                    gel::Game::getInstance()->getWindowHeight() - size.y;
                gel::drawTexture(centerPos,
                                 gel::Color4(1, 1, 1, alphaDuration.progress()),
                                 tex);
        }
}
void ResultScene::hide() { this->finished = false; }

bool ResultScene::isFinished() const { return finished; }

std::string ResultScene::getNextScene() const { return "title"; }

// private
void ResultScene::checkSpaceKey() {
        if (this->phase != 4) {
                return;
        }
        if (glfwGetKey(gel::Game::getInstance()->getWindow(), GLFW_KEY_SPACE) ==
            GLFW_PRESS) {
                this->transStart = true;
        }
        if (!transStart) {
                return;
        }
        transTimer.update();
        if (transTimer.isElapsed()) {
                transTimer.reset();
                this->transStart = false;
                this->finished = true;
        }
}