#include "Spawner.hpp"
Spawner::Spawner(const gel::Vector3& position, const gel::Vector3& rotation,
                 const gel::Vector3& direction)
    : position(position),
      used(false),
      direction(direction),
      rotation(rotation) {}
void Spawner::use() { this->used = true; }
void Spawner::release() { this->used = false; }
gel::Vector3 Spawner::getPosition() const { return position; }
gel::Vector3 Spawner::getDirection() const { return direction; }
gel::Vector3 Spawner::getRotation() const { return rotation; }
bool Spawner::isUsed() const { return used; }