#ifndef GEL_GAME_HPP
#define GEL_GAME_HPP
#include <GLFW/glfw3.h>
namespace gel {
/**
 * Game is provide mainloop and many callback.
 * client will be extend this class for game develop.
 */
class Game {
       public:
        explicit Game();
        virtual ~Game();
        /**
         * start a mainloop.
         * [CAUTION]
         * this method is NOT complete until finish game.
         * should be called at last of main function.
         * @param argc
         * @param argv
         * @param title
         * @param width
         * @param height
         * @return [STATUS-CODE]
         */
        int mainLoop(int argc, char* argv[], const char* title, int width,
                     int height);
        GLFWwindow* getWindow() const;
        float getDeltaTime() const;
        static Game* getInstance();

       protected:
        static Game* instance;
        GLFWwindow* mWindow;
        int mWidth;
        int mHeight;
        long oldTime;
        float deltaTime;
        static void bridgeMouseButton(GLFWwindow* window, int button,
                                      int action, int mods);
        static void bridgeCursorMove(GLFWwindow* window, double x, double y);
        static void bridgeCursorEnter(GLFWwindow* window, int entered);
        static void bridgeScroll(GLFWwindow* window, double xOffset,
                                 double yOffset);
        static void bridgeKey(GLFWwindow* window, int key, int scan, int action,
                              int mods);
        static void bridgeChar(GLFWwindow* window, unsigned int codePoint);
        static void bridgeError(int error, const char* description);

        virtual void onMouseButton(GLFWwindow* window, int button, int action,
                                   int mods);
        virtual void onCursorMove(GLFWwindow* window, double x, double y);
        virtual void onCursorEnter(GLFWwindow* window, int entered);
        virtual void onScroll(GLFWwindow* window, double xOffset,
                              double yOffset);
        virtual void onKey(GLFWwindow* window, int key, int scan, int action,
                           int mods);
        virtual void onChar(GLFWwindow* window, unsigned int codePoint);
        virtual void onError(int error, const char* description);
        virtual void init();
        virtual void update();
        virtual void draw();
};
}  // namespace gel
#endif