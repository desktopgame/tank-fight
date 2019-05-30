#include "Actor.hpp"
Actor::Actor(const std::shared_ptr<gel::IModel>& model,
             const gel::Vector3& position, const gel::Vector3& rotation,
             const gel::Vector3& direction)
    : model(model), direction(direction), aabb(), destroyed(false) {
        transform.position = position;
        transform.rotation = rotation;
        transform.scale = gel::Vector3::one();
        this->aabb = model->getAABB();
}

void Actor::update() {}

void Actor::draw() {}

gel::Vector3 Actor::getPosition() const { return transform.position; }

gel::Vector3 Actor::getRotation() const { return transform.rotation; }

gel::AABB Actor::getAABB() const { return aabb; }

void Actor::destroy() { this->destroyed = true; }

bool Actor::isDestroyed() const { return this->destroyed; }