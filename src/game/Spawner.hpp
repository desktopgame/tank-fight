#ifndef GAME_SPAWNER_HPP
#define GAME_SPAWNER_HPP
#include "../gel/gel.hpp"
class Spawner {
       public:
        explicit Spawner(const gel::Vector3& position);
        void use();
        void release();
        gel::Vector3 getPosition() const;
        bool isUsed() const;

       private:
        gel::Vector3 position;
        bool used;
};
#endif