#ifndef APP_SCENE_TITLESCENE_HPP
#define APP_SCENE_TITLESCENE_HPP
#include "IScene.hpp"
namespace mygame {
class TitleScene : public IScene {
       public:
        TitleScene();
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        bool mFinished;
};
}  // namespace mygame
#endif