#ifndef GAME_SCENE_TITLESCENE_HPP
#define GAME_SCENE_TITLESCENE_HPP
#include <memory>
#include "../../gel/gel.hpp"
class TitleScene : public gel::IScene {
       public:
        TitleScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                   const std::shared_ptr<gel::ModelManager>& modelManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        float tankRotate;
        bool finished;
        gel::Duration alphaDuration;
        std::shared_ptr<gel::TextureManager> textureManager;
        std::shared_ptr<gel::ModelManager> modelManager;
};
#endif