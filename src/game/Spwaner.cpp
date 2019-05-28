#include "Spawner.hpp"
Spawner::Spawner(const gel::Vector3& position)
    : position(position), used(false) {}
void Spawner::use() { this->used = true; }
void Spawner::release() { this->used = false; }
gel::Vector3 Spawner::getPosition() const { return position; }
bool Spawner::isUsed() const { return used; }