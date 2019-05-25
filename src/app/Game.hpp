#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <GLFW/glfw3.h>
namespace mygame {
class Game {
       public:
        explicit Game();
        virtual ~Game();
        int mainLoop(int argc, char* argv[], const char* title, int width,
                     int height);
        static Game* getInstance();

       protected:
        static Game* instance;
        GLFWwindow* mWindow;
        int mWidth;
        int mHeight;
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
}  // namespace mygame
#endif