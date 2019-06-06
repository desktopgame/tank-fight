#include "Game.hpp"
#include <AL/alut.h>
#include <glut.h>
#include <iostream>
#include <memory>
#include <string>
#include "gel.hpp"
#include "ui/GUI.hpp"
namespace gel {
Game* Game::instance = nullptr;

Game::Game() {
        if (Game::instance != nullptr) {
                throw std::logic_error("should be game instance single");
        }
        Game::instance = this;
}

Game::~Game() {}

int Game::mainLoop(int argc, char* argv[], const char* title, int width,
                   int height) {
        this->mWidth = width;
        this->mHeight = height;
        if (!glfwInit()) return -1;
        if (!alutInit(&argc, argv)) return -1;
        // create window
        GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
        this->mWindow = window;
        if (!window) {
                glfwTerminate();
                return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetMouseButtonCallback(window, Game::bridgeMouseButton);
        glfwSetCursorPosCallback(window, Game::bridgeCursorMove);
        glfwSetCursorEnterCallback(window, Game::bridgeCursorEnter);
        glfwSetScrollCallback(window, Game::bridgeScroll);
        glfwSetKeyCallback(window, Game::bridgeKey);
        glfwSetCharCallback(window, Game::bridgeChar);
        init();
        glfwSetTime(0.0);
        // init Imgui
#if DEBUG
        gui::internal::init(window);
#endif
        // start mainloop
        while (!glfwWindowShouldClose(window)) {
#if DEBUG
                gui::internal::newFrame();
#endif
                this->oldTime = glfwGetTime();
                update();
                draw();
                double nowTime = glfwGetTime();
                this->deltaTime = nowTime - oldTime;
                this->oldTime = nowTime;

#if DEBUG
                gui::internal::endFrame();
#endif
        }
#if DEBUG
        gui::internal::destroy();
#endif
        alutExit();
        glfwTerminate();
        return 0;
}

GLFWwindow* Game::getWindow() const { return this->mWindow; }

float Game::getDeltaTime() const { return this->deltaTime; }

Game* Game::getInstance() { return instance; }

int Game::getWindowWidth() const { return mWidth; }

int Game::getWindowHeight() const { return mHeight; }

Vector2 Game::getWindowSize() const { return Vector2(mWidth, mHeight); }

// protected
void Game::init() {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
}
void Game::update() {}

void Game::draw() {}

void Game::bridgeMouseButton(GLFWwindow* window, int button, int action,
                             int mods) {
        Game::instance->onMouseButton(window, button, action, mods);
}

void Game::bridgeCursorMove(GLFWwindow* window, double x, double y) {
        Game::instance->onCursorMove(window, x, y);
}

void Game::bridgeCursorEnter(GLFWwindow* window, int entered) {
        Game::instance->onCursorEnter(window, entered);
}

void Game::bridgeScroll(GLFWwindow* window, double xOffset, double yOffset) {
        Game::instance->onScroll(window, xOffset, yOffset);
}

void Game::bridgeKey(GLFWwindow* window, int key, int scan, int action,
                     int mods) {
        Game::instance->onKey(window, key, scan, action, mods);
}

void Game::bridgeChar(GLFWwindow* window, unsigned int codePoint) {
        Game::instance->onChar(window, codePoint);
}

void Game::bridgeError(int error, const char* description) {
        Game::instance->onError(error, description);
}

void Game::bridgeResize(GLFWwindow* window, int width, int height) {
        Game::instance->onResize(window, width, height);
}

void Game::onMouseButton(GLFWwindow* window, int button, int action, int mods) {
}

void Game::onCursorMove(GLFWwindow* window, double x, double y) {}

void Game::onCursorEnter(GLFWwindow* window, int entered) {}

void Game::onScroll(GLFWwindow* window, double xOffset, double yOffset) {}

void Game::onKey(GLFWwindow* window, int key, int scan, int action, int mods) {}

void Game::onChar(GLFWwindow* window, unsigned int codePoint) {}

void Game::onError(int error, const char* description) {}

void Game::onResize(GLFWwindow* window, int width, int height) {
        this->mWidth = width;
        this->mHeight = height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 0.0, 1.0, -1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}
}  // namespace  gel
