#ifndef GAME_ENEMY_HPP
#define GAME_ENEMY_HPP
#include "../gel/gel.hpp"
class Enemy {
       public:
        explicit Enemy(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& pos, const gel::Vector3& dir);
        void update();
        void draw();

       private:
        std::shared_ptr<gel::IModel> model;
        gel::Vector3 pos;
        gel::Vector3 dir;
        float speed;
};
#endif