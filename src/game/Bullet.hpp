#ifndef GAME_BULLET_HPP
#define GAME_BULLET_HPP
#include "../gel/gel.hpp"
#include <memory>
class Bullet {
       public:
        Bullet(const std::shared_ptr<gel::IModel>& model,
                       const gel::Vector3& position,
                       const gel::Vector3& rotation,
                       const gel::Vector3& direction);
        void update();
        void draw();
        gel::Vector3 getPosition() const;

       private:
	    float speed;
	    std::shared_ptr<gel::IModel> model;
	   	gel::Transform transform;
		gel::Vector3 direction;
};
#endif