#ifndef APP_MYGAME_HPP
#define APP_MYGAME_HPP
#include "Game.hpp"
#include "device/GameDevice.hpp"
#include "scene/SceneManager.hpp"
namespace mygame {
class MyGame : public Game {
       public:
        MyGame();

       protected:
        void init() override;
        void update() override;
        void draw() override;
        float gScrollX;
        float gScrollY;
        float gScrollZ;
        float gRotateY;
        SceneManager sceneManager;
        std::shared_ptr<GameDevice> gameDevice;
};
}  // namespace mygame
#endif