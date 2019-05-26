#include "Object.hpp"
#include <GLFW/glfw3.h>
#include "Context.hpp"
#include "IComponent.hpp"
namespace mygame {
Object::Object(const std::string& name)
    : name(name),
      tag(""),
      children(),
      parent(),
      components(),
      position(),
      scale(1, 1, 1),
      rotate(),
      angle() {}

void Object::setTag(const std::string& tag) { this->tag = tag; }

std::string Object::getTag() const { return tag; }

std::weak_ptr<Object> Object::getParent() const { return parent; }

void Object::addChild(const std::shared_ptr<Object>& child) {
        child->parent = shared_from_this();
        children.push_back(child);
}

std::shared_ptr<Object> Object::getChildAt(size_t index) const {
        return children[index];
}

size_t Object::getChildCount() const { return children.size(); }

void Object::removeFromParent(bool attachToContext) {
        auto shared = parent.lock();
        if (!shared) {
                return;
        }
        shared->removeChild(shared_from_this());
        this->parent.reset();
        if (attachToContext) {
                internal::Context::getInstance().add(shared_from_this());
        }
}

void Object::addComponent(const std::shared_ptr<IComponent>& comp) {
        components.push_back(comp);
        comp->onAwake(shared_from_this());
}

void Object::removeComponent(const std::shared_ptr<IComponent>& comp) {
        auto iter = components.begin();
        while (iter != components.end()) {
                auto e = (*iter);
                if (e == comp) {
                        components.erase(iter);
                        break;
                }
        }
}

std::shared_ptr<IComponent> Object::getComponentAt(size_t index) {
        return components[index];
}

size_t Object::getComponentCount() const { return components.size(); }

void Object::onUpdate() {
        for (auto e : children) {
                e->onUpdate();
        }
        for (auto e : components) {
                e->onUpdate(shared_from_this());
        }
}

void Object::onDraw() {
        ::glPushMatrix();
        ::glTranslatef(position.x, position.y, position.z);
        ::glScalef(scale.x, scale.y, scale.z);
        ::glRotatef(angle, rotate.x, rotate.y, rotate.z);
        for (auto e : children) {
                e->onDraw();
        }
        for (auto e : components) {
                e->onDraw(shared_from_this());
        }
        ::glPopMatrix();
}

void Object::onAwake() {
        for (auto e : children) {
                e->onAwake();
        }
}

void Object::onStart() {
        for (auto e : children) {
                e->onStart();
        }
        for (auto e : components) {
                e->onStart(shared_from_this());
        }
}
void Object::onDestroy() {
        for (auto e : children) {
                e->onDestroy();
        }
}

void Object::removeChild(const std::shared_ptr<Object> child) {
        auto iter = children.begin();
        while (iter != children.end()) {
                auto e = (*iter);
                if (e == child) {
                        children.erase(iter);
                        break;
                }
        }
}
}  // namespace mygame