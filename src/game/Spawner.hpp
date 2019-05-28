#ifndef GAME_SPAWNER_HPP
#define GAME_SPAWNER_HPP
#include "../gel/gel.hpp"
class Spawner {
       public:
        explicit Spawner(const gel::Vector3& position,
                         const gel::Vector3& rotation, const gel::Vector3& direction);
        void use();
        void release();
        gel::Vector3 getRotation() const;
        gel::Vector3 getDirection() const;
        gel::Vector3 getPosition() const;
        bool isUsed() const;

       private:
        gel::Vector3 rotation;
        gel::Vector3 position;
        gel::Vector3 direction;
        bool used;
};
#endif