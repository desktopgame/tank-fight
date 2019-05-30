#ifndef GAME_ENEMY_HPP
#define GAME_ENEMY_HPP
#include "../gel/gel.hpp"
#include "Actor.hpp"
class Enemy : public Actor {
       public:
        explicit Enemy(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& position,
                       const gel::Vector3& rotation,
                       const gel::Vector3& direction);
        void update() override;
        void draw() override;

       private:
        float speed;
};
#endif