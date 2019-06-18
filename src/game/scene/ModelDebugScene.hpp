#ifndef GAME_SCENE_MODELDEBUGSCENE_HPP
#define GAME_SCENE_MODELDEBUGSCENE_HPP
#include <memory>
#include <vector>
#include "../../gel/gel.hpp"
class TextureManager;
class ModelManager;
class ModelDebugScene : public gel::IScene {
       public:
        ModelDebugScene(
            const std::shared_ptr<gel::TextureManager>& textureManager,
            const std::shared_ptr<gel::ModelManager>& modelManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        std::shared_ptr<gel::TextureManager> textureManager;
        std::shared_ptr<gel::ModelManager> modelManager;
        gel::Camera camera;
        bool mFinished;
};
#endif