#ifndef GEL_MODEL_AABB_HPP
#define GEL_MODEL_AABB_HPP
#include <vector>
#include "Matrix4.hpp"
#include "Vector3.hpp"
namespace gel {
/**
 * AABB is Axis-Aligned Bounding Box.
 */
class AABB {
       public:
        explicit AABB();
        explicit AABB(float minX, float minY, float minZ, float maxX,
                      float maxY, float maxZ);
        explicit AABB(std::vector<Vector3> vertexes);
        /**
         * return a all points.
         * @return
         */
        std::vector<Vector3> points() const;
        /**
         * draw a quad of AABB.
         */
        void drawQuad() const;
        /**
         * draw a frame of AABB.
         * @param lineWidth
         */
        void drawFrame(int lineWidth = 10) const;
        /**
         * return a size of AABB.
         * @return
         */
        Vector3 getSize() const;
        float getSizeX() const;
        float getSizeY() const;
        float getSizeZ() const;
        AABB scaled(const Vector3& scale) const;
        AABB transform(const Matrix4& m) const;
        static bool isIntersects(const AABB& a, const AABB& b);
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
}  // namespace gel
#endif