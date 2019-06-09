#include "CubeMap.hpp"
#include <GLFW/glfw3.h>
#include "../model/Color4.hpp"
namespace gel {
CubeMap::CubeMap() : position(0, 0, 0) {}

void CubeMap::draw(const Vector3& size) {
        ::glPushMatrix();
        ::glTranslatef(position.x, position.y, position.z);
        ::glPushAttrib(GL_ENABLE_BIT);  //この時点の各種glEnable()系は退避
        ::glEnable(GL_TEXTURE_2D);
        ::glDisable(GL_DEPTH_TEST);
        ::glDisable(GL_LIGHTING);
        ::glDisable(GL_BLEND);
        ::glEnable(GL_CULL_FACE);
        ::glCullFace(GL_FRONT);
        ::glColor4f(1, 1, 1, 1);

        //+x方向
        ::glBindTexture(GL_TEXTURE_2D, posX);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size.x, size.y, -size.z);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size.x, size.y, -size.z);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size.x, -size.y, -size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size.x, -size.y, -size.z);
        ::glEnd();

        //+z方向
        ::glBindTexture(GL_TEXTURE_2D, posZ);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size.x, -size.y, size.z);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size.x, -size.y, -size.z);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size.x, size.y, -size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size.x, size.y, size.z);
        ::glEnd();

        //-x方向
        ::glBindTexture(GL_TEXTURE_2D, negX);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size.x, size.y, size.z);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size.x, size.y, size.z);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size.x, -size.y, size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size.x, -size.y, size.z);
        ::glEnd();

        //-z方向
        ::glBindTexture(GL_TEXTURE_2D, negZ);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size.x, -size.y, -size.z);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size.x, -size.y, size.z);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size.x, size.y, size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size.x, size.y, -size.z);
        ::glEnd();

        //+y方向
        ::glBindTexture(GL_TEXTURE_2D, posY);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(-size.x, size.y, -size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(-size.x, size.y, size.z);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(size.x, size.y, size.z);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(size.x, size.y, -size.z);
        ::glEnd();

        //-y方向
        ::glBindTexture(GL_TEXTURE_2D, negY);
        ::glBegin(GL_QUADS);
        ::glTexCoord2f(1, 0);
        ::glVertex3f(-size.x, -size.y, -size.z);
        ::glTexCoord2f(0, 0);
        ::glVertex3f(-size.x, -size.y, size.z);
        ::glTexCoord2f(0, 1);
        ::glVertex3f(size.x, -size.y, size.z);
        ::glTexCoord2f(1, 1);
        ::glVertex3f(size.x, -size.y, -size.z);
        ::glEnd();

        ::glPopAttrib();  //各種Enable系をもどす
        ::glPopMatrix();
        ::glCullFace(GL_BACK);
}
}  // namespace gel