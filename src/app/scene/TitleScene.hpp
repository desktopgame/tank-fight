#ifndef APP_SCENE_TITLESCENE_HPP
#define APP_SCENE_TITLESCENE_HPP
#include <memory>
#include "IScene.hpp"
namespace mygame {
class TextureManager;
class TitleScene : public IScene {
       public:
        TitleScene(const std::shared_ptr<TextureManager>& textureManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        std::shared_ptr<TextureManager> mTextureManager;
        bool mFinished;
};
}  // namespace mygame
#endif