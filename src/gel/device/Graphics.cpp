#include "Graphics.hpp"
#include <GLFW/glfw3.h>
#include <glut.h>
#include "../Game.hpp"
namespace gel {
void drawTextureCell(const Vector2& position, const Color4& color, int row,
                     int column, int rowMax, int columnMax,
                     const std::shared_ptr<ITexture>& texture) {
        int w = texture->getWidth();
        int h = texture->getHeight();
        int cw = w / columnMax;
        int ch = h / rowMax;
        int x = column * cw;
        int y = row * ch;
        Rect dstRect = Rect(position.x, position.y, cw, ch);
        drawTexture(dstRect, Rect(x, y, cw, ch), color, texture->getID());
}

void drawTexture(const Vector2& position, const Color4& color,
                 const std::shared_ptr<ITexture>& texture) {
        drawTexture(position, color, texture->getWidth(), texture->getHeight(),
                    texture->getID());
}

void drawTexture(const Vector2& position, const Color4& color, int w, int h,
                 unsigned int tid) {
        drawTexture(Rect(position.x, position.y, w, h), Rect(0, 0, w, h), color,
                    tid);
}

void drawTexture(const Rect& dstRect, const Rect& srcRect, const Color4& color,
                 unsigned int tid) {
        int width = Game::getInstance()->getWindowWidth();
        int height = Game::getInstance()->getWindowHeight();
        glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, width, height, 0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        renderTexture(dstRect, srcRect, color, tid);

        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
        glPopAttrib();
}

void renderTexture(const Rect& dstRect, const Rect& srcRect,
                   const Color4& color, unsigned int tid) {
        // gsBindTexture(id);
        glBindTexture(GL_TEXTURE_2D, tid);

        GLsizei texWidth;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);

        GLsizei texHeight;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT,
                                 &texHeight);

        Rect texCoord(srcRect.left() / texWidth, srcRect.top() / texHeight,
                      srcRect.right() / texWidth, srcRect.bottom() / texHeight);
        glBegin(GL_QUADS);
        glColor4fv((GLfloat*)&color);
        glTexCoord2f(texCoord.left(), texCoord.top());
        glVertex2f(dstRect.left(), dstRect.top());
        glTexCoord2f(texCoord.left(), texCoord.bottom());
        glVertex2f(dstRect.left(), dstRect.bottom());
        glTexCoord2f(texCoord.right(), texCoord.bottom());
        glVertex2f(dstRect.right(), dstRect.bottom());
        glTexCoord2f(texCoord.right(), texCoord.top());
        glVertex2f(dstRect.right(), dstRect.top());
        glEnd();

        // glBindTexture(GL_TEXTURE_2D, 0);
}

void drawField(std::shared_ptr<IModel> model, Vector3 scale, int gridSize,
               int height) {
        auto msize = model->getAABB().getSize();
        for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                        auto pos = Vector3(msize.x * i * scale.x, 0,
                                           msize.z * j * scale.z);
                        glPushMatrix();
                        glTranslatef(pos.x, pos.y, pos.z);
                        glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        glPopMatrix();
                }
        }
        for (int y = 1; y < height; y++) {
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * i * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * gridSize * scale.z);
                        glPushMatrix();
                        glTranslatef(pos.x, pos.y, pos.z);
                        glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * i * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * 0 * scale.z);
                        glPushMatrix();
                        glTranslatef(pos.x, pos.y, pos.z);
                        glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * gridSize * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * i * scale.z);
                        glPushMatrix();
                        glTranslatef(pos.x, pos.y, pos.z);
                        glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        glPopMatrix();
                }
                for (int i = 0; i < gridSize; i++) {
                        auto pos = Vector3(msize.x * 0 * scale.x,
                                           (msize.y * y) * scale.y,
                                           msize.z * i * scale.z);
                        glPushMatrix();
                        glTranslatef(pos.x, pos.y, pos.z);
                        glScalef(scale.x, scale.y, scale.z);
                        model->draw();
                        glPopMatrix();
                }
        }
}

void viewOrthoFixed(int width, int height) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
}

void viewPerspective() {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
}
}  // namespace gel