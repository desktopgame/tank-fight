#include "MyGame.hpp"
#include <glut.h>
#include "scene/ModelDebugScene.hpp"
#include "scene/PlayScene.hpp"
#include "scene/ResultScene.hpp"
#include "scene/TitleScene.hpp"
MyGame::MyGame()
    : sceneManager(),
      gameDevice(gel::GameDevice::make_shared("./assets")),
      playResult(),
      isExitNow(false) {}

void MyGame::init() {
        gameDevice->getContentManager()->load();
        sceneManager.put("title", std::make_shared<TitleScene>(
                                      gameDevice->getTextureManager(),
                                      gameDevice->getModelManager()));
        sceneManager.put("play",
                         std::make_shared<PlayScene>(gameDevice, playResult));
        sceneManager.put("result",
                         std::make_shared<ResultScene>(
                             gameDevice->getTextureManager(), playResult));
        sceneManager.bind("title");

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
        gel::Vector3 sun(0.0, 10, 0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, &sun.x);
        float difLight0[4] = {0.5f, 0.5f, 0.5f, 1.0f};
        glLightfv(GL_LIGHT1, GL_DIFFUSE, difLight0);
        glCullFace(GL_BACK);
}

void MyGame::update() {
        auto win = gel::Game::getInstance()->getWindow();
        if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(win, GL_TRUE);
                isExitNow = true;
                return;
        }
        sceneManager.update();
}

void MyGame::draw() {
        if (isExitNow) {
                return;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glViewport(0, 0, 640, 480);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, (float)width / (float)height, 0.1, 2000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        ;
        // glTranslatef(gScrollX, gScrollY, gScrollZ);
        // glRotatef(gRotateY, 0, 1.0f, 0);
        sceneManager.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
}

void MyGame::onExit() { gameDevice->getContentManager()->unload(); }