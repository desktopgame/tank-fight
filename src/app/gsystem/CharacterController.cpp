#include "CharacterController.hpp"
#include <GLFW/glfw3.h>
#include <glut.h>
#include <cmath>
#include "../Game.hpp"
#include "../model/Matrix4.hpp"
#include "Object.hpp"
namespace mygame {
CharacterController::CharacterController() {}
void CharacterController::onUpdate(const std::shared_ptr<Object>& obj) {
        float increase = 0.001f;
        GLFWwindow* mWindow = Game::getInstance()->getWindow();
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
                obj->angleX -= increase;
        } else if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                obj->angleX += increase;
        }
        if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) {
                obj->angleY -= increase;
        } else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
                obj->angleY += increase;
        }
        if (glfwGetKey(mWindow, 'X') == GLFW_PRESS) {
                obj->position.y -= 0.02f;
        }
        if (glfwGetKey(mWindow, 'Z') == GLFW_PRESS) {
                obj->position.y += 0.02f;
        }
        if (glfwGetKey(mWindow, 'W') == GLFW_PRESS) {
                obj->position += obj->forward() * 0.1f;
        } else if (glfwGetKey(mWindow, 'S') == GLFW_PRESS) {
                obj->position += obj->backward() * 0.1f;
        }
        if (glfwGetKey(mWindow, 'A') == GLFW_PRESS) {
                obj->position += obj->left() * 0.1f;
        } else if (glfwGetKey(mWindow, 'D') == GLFW_PRESS) {
                obj->position += obj->right() * 0.1f;
        }
        auto pos = obj->position + obj->forward();
       gluLookAt(obj->position.x,obj->position.y, obj->position.z, 
       pos.x,pos.y, pos.z, 0.0, 1.0, 0.0);
}
void CharacterController::onDraw(const std::shared_ptr<Object>& obj) {}
void CharacterController::onAwake(const std::shared_ptr<Object>& obj) {}
void CharacterController::onStart(const std::shared_ptr<Object>& obj) {}
}  // namespace mygame