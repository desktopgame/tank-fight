#include "AABB.hpp"
#include <GLFW/glfw3.h>
#include <limits>
namespace mygame {
AABB::AABB() : minX(0), minY(0), minZ(0), maxX(1), maxY(1), maxZ(1) { init(); }
AABB::AABB(float minX, float minY, float minZ, float maxX, float maxY,
           float maxZ)
    : minX(minX), minY(minY), minZ(minZ), maxX(maxX), maxY(maxY), maxZ(maxZ) {
        init();
}

AABB::AABB(std::vector<Vector3> vertexes)
    : minX(std::numeric_limits<float>::max()),
      minY(std::numeric_limits<float>::max()),
      minZ(std::numeric_limits<float>::max()),
      maxX(std::numeric_limits<float>::min()),
      maxY(std::numeric_limits<float>::min()),
      maxZ(std::numeric_limits<float>::min()) {
        auto iter = vertexes.begin();
        while (iter != vertexes.end()) {
                auto v = (*iter);
                if (v.x < minX) {
                        minX = v.x;
                }
                if (v.y < minY) {
                        minY = v.y;
                }
                if (v.z < minZ) {
                        minZ = v.z;
                }
                if (v.x > maxX) {
                        maxX = v.x;
                }
                if (v.y > maxY) {
                        maxY = v.y;
                }
                if (v.z > maxZ) {
                        maxZ = v.z;
                }
                iter++;
        }
        init();
}

std::vector<Vector3> AABB::points() const {
        std::vector<Vector3> a;
        a.push_back(Vector3(minX, minY, maxZ));
        a.push_back(Vector3(maxX, minY, maxZ));

        a.push_back(Vector3(minX, maxY, maxZ));
        a.push_back(Vector3(maxX, maxY, maxZ));

        a.push_back(Vector3(minX, minY, minZ));
        a.push_back(Vector3(maxX, minY, minZ));

        a.push_back(Vector3(minX, maxY, minZ));
        a.push_back(Vector3(maxX, maxY, minZ));
        return a;
}

void AABB::drawQuad() const {
        glBegin(GL_QUADS);
        glVertex3f(this->maxX, this->maxY, this->minZ);
        glVertex3f(this->minX, this->maxY, this->minZ);
        glVertex3f(this->minX, this->maxY, this->maxZ);
        glVertex3f(this->maxX, this->maxY, this->maxZ);
        glVertex3f(this->maxX, this->minY, this->minZ);
        glVertex3f(this->minX, this->minY, this->minZ);
        glVertex3f(this->minX, this->minY, this->maxZ);
        glVertex3f(this->maxX, this->minY, this->maxZ);
        glVertex3f(this->maxX, this->maxY, this->maxZ);
        glVertex3f(this->minX, this->maxY, this->maxZ);
        glVertex3f(this->minX, this->minY, this->maxZ);
        glVertex3f(this->maxX, this->minY, this->maxZ);
        glVertex3f(this->maxX, this->maxY, this->minZ);
        glVertex3f(this->minX, this->maxY, this->minZ);
        glVertex3f(this->minX, this->minY, this->minZ);
        glVertex3f(this->maxX, this->minY, this->minZ);
        glVertex3f(this->minX, this->maxY, this->maxZ);
        glVertex3f(this->minX, this->maxY, this->minZ);
        glVertex3f(this->minX, this->minY, this->minZ);
        glVertex3f(this->minX, this->minY, this->maxZ);
        glVertex3f(this->maxX, this->maxY, this->maxZ);
        glVertex3f(this->maxX, this->maxY, this->minZ);
        glVertex3f(this->maxX, this->minY, this->minZ);
        glVertex3f(this->maxX, this->minY, this->maxZ);
        glEnd();
}

void AABB::drawFrame(int lineWidth) const {
        glLineWidth(lineWidth);
        glBegin(GL_LINES);
        glVertex3f(minX, minY, maxZ);
        glVertex3f(maxX, minY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, maxY, maxZ);
        glVertex3f(maxX, maxY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, minY, minZ);
        glVertex3f(maxX, minY, minZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, maxY, minZ);
        glVertex3f(maxX, maxY, minZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, minY, minZ);
        glVertex3f(minX, minY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, maxY, minZ);
        glVertex3f(minX, maxY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(maxX, minY, minZ);
        glVertex3f(maxX, minY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(maxX, maxY, minZ);
        glVertex3f(maxX, maxY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, minY, minZ);
        glVertex3f(minX, maxY, minZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(maxX, minY, minZ);
        glVertex3f(maxX, maxY, minZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(minX, minY, maxZ);
        glVertex3f(minX, maxY, maxZ);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(maxX, minY, maxZ);
        glVertex3f(maxX, maxY, maxZ);
        glEnd();
}

Vector3 AABB::getSize() const {
        return Vector3(getSizeX(), getSizeY(), getSizeZ());
}

float AABB::getSizeX() const { return maxX - minX; }

float AABB::getSizeY() const { return maxY - minY; }

float AABB::getSizeZ() const { return maxZ - minZ; }

void AABB::init() {
        this->center =
            Vector3(minX + (maxX - minX) / 2, minY + (maxY - minY) / 2,
                    minZ + (maxZ - minZ) / 2);
        this->radius =
            Vector3((maxX - minX) / 2, (maxY - minY) / 2, (maxZ - minZ) / 2);
}
}  // namespace mygame