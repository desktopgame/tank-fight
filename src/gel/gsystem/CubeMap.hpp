#ifndef GEL_GSYSTEM_CUBEMAP_HPP
#define GEL_GSYSTEM_CUBEMAP_HPP
#include "../model/Vector3.hpp"
namespace gel {
class CubeMap {
       public:
        explicit CubeMap();
        void draw(const Vector3& size);
        Vector3 position;
        unsigned int posX;
        unsigned int negX;
        unsigned int posY;
        unsigned int negY;
        unsigned int posZ;
        unsigned int negZ;
};
}  // namespace gel
#endif