#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <glut.h>
#include <algorithm>
#include <cmath>
#include "../Game.hpp"
namespace gel {
Camera::Camera() : transform() {}

void Camera::beginDraw() const {
        ::glPushMatrix();
        ::glLoadIdentity();
        auto pos = transform.position;
        auto lookat = pos + transform.forward();
        //::glTranslatef(pos.x, pos.y, pos.z);
        //::glRotatef(transform.rotation.y, 0, 1, 0);
        //::glRotatef(transform.rotation.x, 1, 0, 0);
        //::glRotatef(transform.angleZ, 0, 0, 1);
        //::glTranslatef(-pos.x, -pos.y, -pos.z);
        ::gluLookAt(pos.x, pos.y, pos.z, lookat.x, lookat.y, lookat.z, 0.0, 1.0,
                    0.0);
}

void Camera::endDraw() const { ::glPopMatrix(); }

void Camera::debugControl() {
        float increase = 0.001f;
        GLFWwindow* mWindow = Game::getInstance()->getWindow();
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT)) {
                increase = 0.5;
        }
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
                transform.rotation.x += increase * 50;
        } else if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                transform.rotation.x -= increase * 50;
        }
        if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) {
                transform.rotation.y += increase * 50;
        } else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
                transform.rotation.y -= increase * 50;
        }
        if (glfwGetKey(mWindow, 'X') == GLFW_PRESS) {
                transform.position.y -= 0.02f;
        }
        if (glfwGetKey(mWindow, 'Z') == GLFW_PRESS) {
                transform.position.y += 0.02f;
        }
        if (glfwGetKey(mWindow, 'W') == GLFW_PRESS) {
                transform.position +=
                    Vector3(1, 0, 1) * transform.forward() * 0.1f;
        } else if (glfwGetKey(mWindow, 'S') == GLFW_PRESS) {
                transform.position +=
                    Vector3(1, 0, 1) * transform.backward() * 0.1f;
        }
        if (glfwGetKey(mWindow, 'A') == GLFW_PRESS) {
                transform.position +=
                    Vector3(1, 0, 1) * transform.left() * 0.1f;
        } else if (glfwGetKey(mWindow, 'D') == GLFW_PRESS) {
                transform.position +=
                    Vector3(1, 0, 1) * transform.right() * 0.1f;
        }
        transform.rotation.y =
            std::max(-90.f, std::min(90.f, transform.rotation.y));
}
}  // namespace gel