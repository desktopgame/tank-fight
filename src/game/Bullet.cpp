#include "Bullet.hpp"
#include "scene/PlayScene.hpp"
Bullet::Bullet(const std::shared_ptr<gel::IModel>& model,
               const gel::Vector3& position, const gel::Vector3& rotation,
               const gel::Vector3& direction)
    : speed(1), model(model), transform(), direction(direction) {
        transform.position = position;
        transform.rotation = rotation;
        transform.scale =
            gel::Vector3(PlayScene::TANK_SCALE * 10, PlayScene::TANK_SCALE * 10,
                         PlayScene::TANK_SCALE * 10);
}

void Bullet::update() {
        transform.position +=
            (direction * speed * gel::Game::getInstance()->getDeltaTime());
}

void Bullet::draw() {
        ::glPushMatrix();
        ::glPushMatrix();
        ::glTranslatef(transform.position.x, transform.position.y,
                       transform.position.z);
        //::glRotatef(transform.rotation.y, 0, 1, 0);
        //::glRotatef(transform.rotation.x, 1, 0, 0);
        //::glRotatef(transform.rotation.z, 0, 0, 1);
        ::glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
        model->draw();
        ::glPopMatrix();
        ::glPopMatrix();
}

gel::Vector3 Bullet::getPosition() const { return transform.position; }