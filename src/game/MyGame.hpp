#ifndef GAME_MYGAME_HPP
#define GAME_MYGAME_HPP
#include "../gel/gel.hpp"
#include "PlayResult.hpp"
class MyGame : public gel::Game {
       public:
        MyGame();

       protected:
        void init() override;
        void update() override;
        void draw() override;
        PlayResult playResult;
        gel::SceneManager sceneManager;
        std::shared_ptr<gel::GameDevice> gameDevice;
};
#endif