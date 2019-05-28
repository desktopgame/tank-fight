#include "MyGame.hpp"
#include <glut.h>
#include "scene/ModelDebugScene.hpp"
#include "scene/TitleScene.hpp"
MyGame::MyGame()
    : sceneManager(), gameDevice(gel::GameDevice::make_shared("./assets")) {}

void MyGame::init() {
        gameDevice->getContentManager()->load();
        sceneManager.put("title", std::make_shared<TitleScene>(
                                      gameDevice->getTextureManager(),
                                      gameDevice->getModelManager()));
        sceneManager.put("modelDebug", std::make_shared<ModelDebugScene>(
                                           gameDevice->getTextureManager(),
                                           gameDevice->getModelManager()));
        sceneManager.bind("title");
#if DEBUG
        // sceneManager.bind("modelDebug");
#endif
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

void MyGame::update() { sceneManager.update(); }

void MyGame::draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glViewport(0, 0, 640, 480);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, 640 / 480, 0.1, 2000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 0.1, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        // glTranslatef(gScrollX, gScrollY, gScrollZ);
        // glRotatef(gRotateY, 0, 1.0f, 0);
        sceneManager.draw();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
}