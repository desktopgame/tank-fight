#include <GLFW/glfw3.h>
#include "content/ContentManager.hpp"
#include "content/EchoPipeline.hpp"
#include "content/ProxyPipeline.hpp"
#include "scene/SceneManager.hpp"
#include "scene/TitleScene.hpp"

int main(void) {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit()) return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window) {
                glfwTerminate();
                return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        mygame::ContentManager contentMgr = mygame::ContentManager("./assets");
        contentMgr.add(
            std::make_shared<mygame::ProxyPipeline<mygame::EchoPipeline> >(
                ".wav"));
        contentMgr.load();
        mygame::SceneManager sceneMgr;
        sceneMgr.put("title", std::make_shared<mygame::TitleScene>());
        sceneMgr.bind("title");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
                sceneMgr.update();
                sceneMgr.draw();

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
        }

        glfwTerminate();
        return 0;
}