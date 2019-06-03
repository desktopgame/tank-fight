#ifndef GEL_UI_GUI_HPP
#define GEL_UI_GUI_HPP
#include <GLFW/glfw3.h>
namespace gel {
/**
 * GUI is ui utility for game develop.
 */
namespace gui {
namespace internal {
void init(GLFWwindow* window);
void destroy();
}  // namespace internal

/**
 * create a new frame.
 */
void newFrame();
/**
 * destroy a last frame.
 */
void endFrame();
/**
 * render GUI.
 */
void render();
};  // namespace gui
}  // namespace gel
#endif