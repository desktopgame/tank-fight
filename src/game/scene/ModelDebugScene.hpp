#ifndef GAME_SCENE_MODELDEBUGSCENE_HPP
#define GAME_SCENE_MODELDEBUGSCENE_HPP
#include <memory>
#include <vector>
#include "../../gel/gel.hpp"
namespace gel {
class TextureManager;
class ModelManager;
class ModelDebugScene : public IScene {
       public:
        ModelDebugScene(const std::shared_ptr<TextureManager>& textureManager,
                        const std::shared_ptr<ModelManager>& modelManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        std::shared_ptr<TextureManager> mTextureManager;
        std::shared_ptr<ModelManager> mModelManager;
        Camera camera;
        bool mFinished;
};
}  // namespace gel
#endif