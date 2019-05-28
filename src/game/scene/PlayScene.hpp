#ifndef GAME_SCENE_TITLESCENE_HPP
#define GAME_SCENE_TITLESCENE_HPP
#include <memory>
#include <vector>
#include "../../gel/gel.hpp"
#include "../Spawner.hpp"
class TextureManager;
class ModelManager;
class PlayScene : public gel::IScene {
       public:
        PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                  const std::shared_ptr<gel::ModelManager>& modelManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        static float BLOCK_SCALE;
        static float TANK_SCALE;
        void initSpawners(float blockScale);
        std::vector<std::shared_ptr<Spawner> > spawners;
        std::shared_ptr<gel::TextureManager> mTextureManager;
        std::shared_ptr<gel::ModelManager> mModelManager;
        gel::Camera camera;
        bool mFinished;
};
#endif