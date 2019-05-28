#ifndef APP_MYGAME_HPP
#define APP_MYGAME_HPP
#include "Game.hpp"
#include "device/GameDevice.hpp"
#include "scene/SceneManager.hpp"
namespace gel {
class MyGame : public Game {
       public:
        MyGame();

       protected:
        void init() override;
        void update() override;
        void draw() override;
        SceneManager sceneManager;
        std::shared_ptr<GameDevice> gameDevice;
};
}  // namespace gel
#endif