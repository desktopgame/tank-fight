#ifndef GAME_ACTOR_HPP
#define GAME_ACTOR_HPP
#include <memory>
#include "../gel/gel.hpp"
class Actor {
       public:
        explicit Actor(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& position,
                       const gel::Vector3& rotation,
                       const gel::Vector3& direction);
        virtual ~Actor() = default;
        virtual void update();
        virtual void draw();

        gel::Vector3 getPosition() const;
        void destroy();
        bool isDestroyed() const;

       private:
        bool destroyed;

       protected:
        std::shared_ptr<gel::IModel> model;
        gel::Transform transform;
        gel::Vector3 direction;
        gel::AABB aabb;
};
#endif