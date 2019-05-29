#ifndef GAME_ENEMY_HPP
#define GAME_ENEMY_HPP
#include "../gel/gel.hpp"
class Enemy {
       public:
        explicit Enemy(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& position,
                       const gel::Vector3& rotation,
                       const gel::Vector3& direction);
        void update();
        void draw();
        gel::Vector3 getPosition() const;

       private:
        std::shared_ptr<gel::IModel> model;
        gel::Transform transform;
        gel::Vector3 direction;
        gel::AABB aabb;
        float speed;
};
#endif