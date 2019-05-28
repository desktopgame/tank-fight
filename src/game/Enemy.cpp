#include "Enemy.hpp"
#include "scene/PlayScene.hpp"

Enemy::Enemy(const std::shared_ptr<gel::IModel>& model,
             const gel::Vector3& position, const gel::Vector3& rotation)
    : model(model), position(position), rotation(rotation), speed(1) {}

void Enemy::update() {}

void Enemy::draw() {
        ::glPushMatrix();
        ::glTranslatef(position.x, position.y, position.z);
        ::glRotatef(rotation.y, 0, 1, 0);
        ::glRotatef(rotation.x, 1, 0, 0);
        ::glRotatef(rotation.z, 0, 0, 1);
        ::glScalef(PlayScene::TANK_SCALE, PlayScene::TANK_SCALE,
                   PlayScene::TANK_SCALE);
        model->draw();
        ::glPopMatrix();
}