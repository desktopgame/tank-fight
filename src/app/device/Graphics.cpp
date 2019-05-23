#include "Graphics.hpp"
#include <GLFW/glfw3.h>
namespace mygame {
void drawTexture(Vector2 leftBottom, Vector2 leftTop, Vector2 rightTop,
                 Vector2 rightBottom, unsigned int tid) {
        ::glEnable(GL_TEXTURE_2D);
        ::glBindTexture(GL_TEXTURE_2D, tid);
        ::glEnable(GL_ALPHA_TEST);
        // glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        ::glBegin(GL_POLYGON);
        // left bottom
        ::glTexCoord2f(0.0f, 1.0f);
        ::glVertex2d(leftBottom.x, leftBottom.y);
        // left top
        ::glTexCoord2f(0.0f, 0.0f);
        ::glVertex2d(leftTop.x, leftTop.y);
        // right top
        ::glTexCoord2f(1.0f, 0.0f);
        ::glVertex2d(rightTop.x, rightTop.y);
        // right bottom
        ::glTexCoord2f(1.0f, 1.0f);
        ::glVertex2d(rightBottom.x, rightBottom.y);
        ::glEnd();
        ::glDisable(GL_ALPHA_TEST);
        ::glDisable(GL_TEXTURE_2D);
}
}  // namespace mygame