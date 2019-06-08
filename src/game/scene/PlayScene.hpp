#ifndef GAME_SCENE_PLAYSCENE_HPP
#define GAME_SCENE_PLAYSCENE_HPP
#include <memory>
#include <vector>
#include "../../gel/gel.hpp"
#include "../Bullet.hpp"
#include "../Enemy.hpp"
#include "../HitCache.hpp"
#include "../Spawner.hpp"
class TextureManager;
class ModelManager;
class PlayScene : public gel::IScene {
       public:
        static float BLOCK_SCALE;
        static float TANK_SCALE;
        static float BULLET_SCALE;
        static float BULLET_SPEED;
        static float MOVE_SPEED;
        static float ROTATE_SPEED;
        static int PLAY_TIME;
        PlayScene(const std::shared_ptr<gel::TextureManager>& textureManager,
                  const std::shared_ptr<gel::ModelManager>& modelManager);
        void show() override;
        void update() override;
        void draw() override;
        std::string getNextScene() const override;
        bool isFinished() const override;
        void hide() override;

       private:
        template <typename T>
        inline void remove_if(std::vector<T>& v) {
                auto end = std::remove_if(v.begin(), v.end(), [&](auto& e) {
                        auto pos = e->getPosition();
                        return e->isDestroyed() ||
                               (pos.x < (-2 * blockAABBSize.x * BLOCK_SCALE) ||
                                pos.x > (46 * blockAABBSize.x * BLOCK_SCALE) ||
                                pos.z < (-2 * blockAABBSize.z * BLOCK_SCALE) ||
                                pos.z > (46 * blockAABBSize.z * BLOCK_SCALE));
                });
                v.erase(end, v.end());
        }

        void initSpawners(float blockScale);
        void spawn();
        void spawn(int n);
        void movePlayer();
        void fireBullet();
        void checkPlayTime();
        std::shared_ptr<Bullet> newBullet();
        void drawIMGUI();

        static std::vector<HitCache> actorToCache(
            const std::vector<std::shared_ptr<Actor> > actors, float scale);

        bool fired;
        gel::Random random;
        gel::Timer spawnTimer;
        gel::Timer fireTimer;
        gel::Timer playTimer;
        int playTime;
        gel::Number playTimeUI;
        gel::Vector3 blockAABBSize;
        std::vector<std::shared_ptr<Bullet> > bullets;
        std::vector<std::shared_ptr<Enemy> > enemies;
        std::vector<std::shared_ptr<Spawner> > spawners;
        std::shared_ptr<gel::TextureManager> mTextureManager;
        std::shared_ptr<gel::ModelManager> mModelManager;
        gel::Camera camera;
        bool mFinished;
};
#endif