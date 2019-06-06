#include "Graphics.hpp"
#include <GLFW/glfw3.h>
namespace gel {
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

void drawField(std::shared_ptr<IModel> model, Vector3 scale, int gridSize,
               int height) {
        auto msize = model->getAABB().getSize();
        for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                        auto pos = Vector3(msize.x * i * scale.x, 0,
                                           msize.z * j * scale.z);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        ::glPopMatrix();
                }
        }
        for (int y = 1; y < height; y++) {
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * i * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * gridSize * scale.z);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        ::glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * i * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * 0 * scale.z);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        ::glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * gridSize * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * i * scale.z);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        ::glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * 0 * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * i * scale.z);
                        ::glPushMatrix();
                        ::glTranslatef(pos.x, pos.y, pos.z);
                        ::glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        ::glPopMatrix();
                }
        }
}

void viewOrthoFixed(int width, int height) {
        ::glMatrixMode(GL_PROJECTION);
        ::glPushMatrix();
        ::glLoadIdentity();
        ::glOrtho(0, width, height, 0, -1, 1);
        ::glMatrixMode(GL_MODELVIEW);
        ::glPushMatrix();
        ::glLoadIdentity();
}

void viewPerspective() {
        ::glMatrixMode(GL_PROJECTION);
        ::glPopMatrix();
        ::glMatrixMode(GL_MODELVIEW);
        ::glPopMatrix();
}
}  // namespace gel