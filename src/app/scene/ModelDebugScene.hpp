#ifndef APP_SCENE_MODELDEBUGSCENE_HPP
#define APP_SCENE_MODELDEBUGSCENE_HPP
#include <memory>
#include <vector>
#include "../gsystem/Camera.hpp"
#include "IScene.hpp"
namespace mygame {
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
}  // namespace mygame
#endif