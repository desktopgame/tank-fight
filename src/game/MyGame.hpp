#ifndef GAME_MYGAME_HPP
#define GAME_MYGAME_HPP
#include "../gel/gel.hpp"
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