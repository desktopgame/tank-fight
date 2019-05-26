#ifndef APP_MODEL_AABB_HPP
#define APP_MODEL_AABB_HPP
#include <vector>
#include "Vector3.hpp"
namespace mygame {
/**
 * AABB is Axis-Aligned Bounding Box.
 */
class AABB {
       public:
        explicit AABB();
        explicit AABB(float minX, float minY, float minZ, float maxX,
                      float maxY, float maxZ);
        explicit AABB(std::vector<Vector3> vertexes);
        std::vector<Vector3> points() const;
        void drawQuad() const;
        void drawFrame(int lineWidth = 10) const;
        Vector3 getSize() const;
        float getSizeX() const;
        float getSizeY() const;
        float getSizeZ() const;
        Vector3 center;
        Vector3 radius;
        float minX;
        float minY;
        float minZ;
        float maxX;
        float maxY;
        float maxZ;

       private:
        void init();
};
}  // namespace mygame
#endif