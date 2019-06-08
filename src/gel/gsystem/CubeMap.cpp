#include "CubeMap.hpp"
#include <GLFW/glfw3.h>
namespace gel {
CubeMap::CubeMap() {}

void CubeMap::draw(float size) {
        ::glPushAttrib(GL_ENABLE_BIT);  //この時点の各種glEnable()系は退避
        ::glEnable(GL_TEXTURE_2D);
        ::glDisable(GL_DEPTH_TEST);
        ::glDisable(GL_LIGHTING);
        ::glDisable(GL_BLEND);

        //+x方向
        ::glBindTexture(GL_TEXTURE_2D, posX);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size, -size, -size);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size, -size, -size);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size, size, -size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size, size, -size);
        ::glEnd();

        //+z方向
        ::glBindTexture(GL_TEXTURE_2D, posZ);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size, -size, size);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size, -size, -size);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size, size, -size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size, size, size);
        ::glEnd();

        //-x方向
        ::glBindTexture(GL_TEXTURE_2D, negX);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size, -size, size);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size, -size, size);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size, size, size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size, size, size);
        ::glEnd();

        //-z方向
        ::glBindTexture(GL_TEXTURE_2D, negZ);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size, -size, -size);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size, -size, size);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size, size, size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size, size, -size);
        ::glEnd();

        //+y方向
        ::glBindTexture(GL_TEXTURE_2D, posY);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size, size, -size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size, size, size);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size, size, size);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size, size, -size);
        ::glEnd();

        //-y方向
        ::glBindTexture(GL_TEXTURE_2D, negY);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size, -size, -size);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size, -size, size);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size, -size, size);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size, -size, -size);
        ::glEnd();

        ::glPopAttrib();  //各種Enable系をもどす
}
}  // namespace gel