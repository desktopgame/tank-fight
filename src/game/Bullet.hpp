#ifndef GAME_BULLET_HPP
#define GAME_BULLET_HPP
#include <memory>
#include "../gel/gel.hpp"
#include "Actor.hpp"
class Bullet : public Actor {
       public:
        Bullet(const std::shared_ptr<gel::IModel>& model,
               const gel::Vector3& position, const gel::Vector3& rotation,
               const gel::Vector3& direction);
        void update() override;
        void draw() override;

        void setSpeed(float speed);
        float getSpeed() const;

       private:
        float speed;
};
#endif