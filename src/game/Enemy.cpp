#include "Enemy.hpp"
#include "scene/PlayScene.hpp"

Enemy::Enemy(const std::shared_ptr<gel::IModel>& model, const gel::Vector3& pos,
             const gel::Vector3& dir)
    : model(model), pos(pos), dir(dir), speed(1) {}

void Enemy::update() {
        this->pos += (dir * speed * gel::Game::getInstance()->getDeltaTime());
}

void Enemy::draw() {
        ::glPushMatrix();
        ::glTranslatef(pos.x, pos.y, pos.z);
        ::glScalef(PlayScene::TANK_SCALE, PlayScene::TANK_SCALE,
                   PlayScene::TANK_SCALE);
        model->draw();
        ::glPopMatrix();
}