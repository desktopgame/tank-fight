#include <AL/alut.h>
#include <GLFW/glfw3.h>
#include <glut.h>
#include <memory>
#include <string>
#include "content/BmpPipeline.hpp"
#include "content/ContentManager.hpp"
#include "content/EchoPipeline.hpp"
#include "content/FbxPipeline.hpp"
#include "content/ObjPipeline.hpp"
#include "content/PngPipeline.hpp"
#include "content/ProxyPipeline.hpp"
#include "content/WavePipeline.hpp"
#include "device/AudioManager.hpp"
#include "device/ModelManager.hpp"
#include "device/TextureManager.hpp"
#include "scene/SceneManager.hpp"
#include "scene/TitleScene.hpp"

static void render_2d() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0.0, 640, 480, 0.0, -1.0, 1.0);
}

static void render_3d() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 640, 480);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(30.0, 640 / 480, 0.1, 2000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 200.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(90.0f, 0, 1.0f, 0);
}

static void init_gl() {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
}

int main(int argc, char* argv[]) {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit()) return -1;
        if (!alutInit(&argc, argv)) return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window) {
                glfwTerminate();
                return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        auto modelMgr = std::make_shared<mygame::ModelManager>();
        auto textureMgr = std::make_shared<mygame::TextureManager>();
        auto audioMgr = std::make_shared<mygame::AudioManager>();
        mygame::ContentManager contentMgr = mygame::ContentManager("./assets");
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::WavePipeline> >(
                ".wav", audioMgr));
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::BmpPipeline> >(
                ".bmp", textureMgr));
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::PngPipeline> >(
                ".png", textureMgr));
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::FbxPipeline> >(
                ".fbx", modelMgr));
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::ObjPipeline> >(
                ".obj", modelMgr));
        contentMgr.load();
        // audioMgr->play("./assets/audio/se_maou_test.wav");
        mygame::SceneManager sceneMgr;
        sceneMgr.put("title", std::make_shared<mygame::TitleScene>(textureMgr,
                                                                   modelMgr));
        sceneMgr.bind("title");
        init_gl();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
                /* Render here */
                render_3d();
                sceneMgr.update();
                sceneMgr.draw();

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
        }

        alutExit();
        glfwTerminate();
        return 0;
}