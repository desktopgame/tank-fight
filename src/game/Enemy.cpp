#include "Enemy.hpp"
#include "scene/PlayScene.hpp"

Enemy::Enemy(const std::shared_ptr<gel::IModel>& model,
             const gel::Vector3& position, const gel::Vector3& rotation,
             const gel::Vector3& direction)
    : Actor(model, position, rotation, direction), speed(1) {
        transform.position = position;
        transform.rotation = rotation;
        transform.scale =
            gel::Vector3(PlayScene::TANK_SCALE, PlayScene::TANK_SCALE,
                         PlayScene::TANK_SCALE);
        this->aabb = model->getAABB();
}

void Enemy::update() {
        transform.position +=
            (direction * speed * gel::Game::getInstance()->getDeltaTime());
}

void Enemy::draw() {
        glPushMatrix();
        glTranslatef(transform.position.x, transform.position.y,
                     transform.position.z);
        glRotatef(transform.rotation.y, 0, 1, 0);
        glRotatef(transform.rotation.x, 1, 0, 0);
        glRotatef(transform.rotation.z, 0, 0, 1);
        glScalef(PlayScene::TANK_SCALE, PlayScene::TANK_SCALE,
                 PlayScene::TANK_SCALE);
        model->draw();
#if DEBUG
        aabb.drawFrame();
#endif
        glPopMatrix();
}
