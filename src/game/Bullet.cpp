#include "Bullet.hpp"
#include "scene/PlayScene.hpp"
Bullet::Bullet(const std::shared_ptr<gel::IModel>& model,
               const gel::Vector3& position, const gel::Vector3& rotation,
               const gel::Vector3& direction)
    : Actor(model, position, rotation, direction), speed(1) {
        transform.position = position;
        transform.rotation = rotation;
        transform.scale = gel::Vector3(PlayScene::TANK_SCALE * 0.1f,
                                       PlayScene::TANK_SCALE * 0.1f,
                                       PlayScene::TANK_SCALE * 0.1f);
        this->aabb = model->getAABB();
}

void Bullet::update() {
        transform.position +=
            (direction * speed * gel::Game::getInstance()->getDeltaTime());
}

void Bullet::draw() {
        glPushMatrix();
        glPushMatrix();
        glTranslatef(transform.position.x, transform.position.y,
                     transform.position.z);
        // glRotatef(transform.rotation.y, 0, 1, 0);
        glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
        model->draw();
#if DEBUG
        aabb.drawFrame();
#endif
        glPopMatrix();
        glPopMatrix();
}

void Bullet::setSpeed(float speed) { this->speed = speed; }

float Bullet::getSpeed() const { return speed; }