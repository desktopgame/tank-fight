#ifndef GAME_SCENE_PLAYSCENE_HPP
#define GAME_SCENE_PLAYSCENE_HPP
#include <alut.h>
#include <memory>
#include <vector>
#include "../../gel/gel.hpp"
#include "../Bullet.hpp"
#include "../Enemy.hpp"
#include "../HitCache.hpp"
#include "../PlayResult.hpp"
#include "../Spawner.hpp"
class TextureManager;
class ModelManager;
class PlayScene : public gel::IScene {
       public:
        static const float BLOCK_SCALE;
        static const float TANK_SCALE;
        static const float BULLET_SCALE;
        static const float BULLET_SPEED;
        static const float MOVE_SPEED;
        static const float ROTATE_SPEED;
        static const int PLAY_TIME;
        static const int STAGE_SIZE;
        static const int STAGE_CENTER_X;
        static const int STAGE_CENTER_Z;
        static const int KILL_POINT;
        static const int SPAWN_MIN;
        static const int SPAWN_MAX;
        PlayScene(const std::shared_ptr<gel::GameDevice>& gameDevice,
                  PlayResult& playResult);
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
                               (pos.x < stageMinX || pos.x > stageMaxX ||
                                pos.z < stageMinZ || pos.z > stageMaxZ);
                });
                v.erase(end, v.end());
        }

        void initSkyBox();
        void initSpawners(float blockScale);
        void spawn();
        void spawn(int n);
        void movePlayer();
        void fireBullet();
        void checkPlayTime();
        std::shared_ptr<Bullet> newBullet();
        void drawIMGUI();
        void drawTime();
        std::shared_ptr<gel::AudioManager> audioManager;
        std::shared_ptr<gel::TextureManager> mTextureManager;
        std::shared_ptr<gel::ModelManager> mModelManager;

        std::vector<HitCache> actorToCache(
            const std::vector<std::shared_ptr<Actor> > actors, float scale);

        int kill;
        bool fired;
        float stageMinX;
        float stageMaxX;
        float stageMinZ;
        float stageMaxZ;
        ALuint bgmSrc;
        ALuint explosionSrc;
        PlayResult& playResult;
        gel::Random random;
        gel::Timer spawnTimer;
        gel::Timer fireTimer;
        gel::Timer playTimer;
        gel::CubeMap skybox;
        int playTime;
        gel::Number playTimeUI;
        gel::Vector3 blockAABBSize;
        std::vector<std::shared_ptr<Bullet> > bullets;
        std::vector<std::shared_ptr<Enemy> > enemies;
        std::vector<std::shared_ptr<Spawner> > spawners;
        gel::Camera camera;
        bool mFinished;
};
#endif