#include <AL/alut.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "content/BmpPipeline.hpp"
#include "content/PngPipeline.hpp"
#include "content/ContentManager.hpp"
#include "content/EchoPipeline.hpp"
#include "content/ProxyPipeline.hpp"
#include "content/WavePipeline.hpp"
#include "device/AudioManager.hpp"
#include "device/TextureManager.hpp"
#include "scene/SceneManager.hpp"
#include "scene/TitleScene.hpp"

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
        contentMgr.load();
        // audioMgr->play("./assets/audio/se_maou_test.wav");
        mygame::SceneManager sceneMgr;
        sceneMgr.put("title", std::make_shared<mygame::TitleScene>(textureMgr));
        sceneMgr.bind("title");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                glOrtho(0.0, 640, 480, 0.0, -1.0, 1.0);
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