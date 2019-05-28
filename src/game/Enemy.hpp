#ifndef GAME_ENEMY_HPP
#define GAME_ENEMY_HPP
#include "../gel/gel.hpp"
class Enemy {
       public:
        explicit Enemy(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& position,
                       const gel::Vector3& rotation);
        void update();
        void draw();

       private:
        std::shared_ptr<gel::IModel> model;
        gel::Vector3 position;
        gel::Vector3 rotation;
        float speed;
};
#endif