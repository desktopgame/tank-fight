#include "MyGame.hpp"
#include <glut.h>
#include "scene/TitleScene.hpp"
namespace mygame {
MyGame::MyGame()
    : sceneManager(), gameDevice(GameDevice::make_shared("./assets")) {}

void MyGame::init() {
        gameDevice->getContentManager()->load();
        sceneManager.put("title", std::make_shared<mygame::TitleScene>(
                                      gameDevice->getTextureManager(),
                                      gameDevice->getModelManager()));
        sceneManager.bind("title");
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
}

void MyGame::update() {
        float increase = 0.001f;
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
                gScrollX -= increase;
        } else if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                gScrollX += increase;
        }
        if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS) {
                gScrollY -= increase;
        } else if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
                gScrollY += increase;
        }
        if (glfwGetKey(mWindow, 'W') == GLFW_PRESS) {
                gScrollZ -= increase;
        } else if (glfwGetKey(mWindow, 'S') == GLFW_PRESS) {
                gScrollZ += increase;
        }
        if (glfwGetKey(mWindow, 'A') == GLFW_PRESS) {
                gRotateY -= increase;
        } else if (glfwGetKey(mWindow, 'D') == GLFW_PRESS) {
                gRotateY += increase;
        }
        sceneManager.update();
}

void MyGame::draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glViewport(0, 0, 640, 480);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, 640 / 480, 0.1, 2000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 0.1, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glTranslatef(gScrollX, gScrollY, gScrollZ);
        glRotatef(gRotateY, 0, 1.0f, 0);
        sceneManager.draw();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
}
}  // namespace mygame