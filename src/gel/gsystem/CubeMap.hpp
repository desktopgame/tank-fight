#ifndef GEL_GSYSTEM_CUBEMAP_HPP
#define GEL_GSYSTEM_CUBEMAP_HPP
namespace gel {
class CubeMap {
       public:
        explicit CubeMap();
        void draw(float size);
        unsigned int posX;
        unsigned int negX;
        unsigned int posY;
        unsigned int negY;
        unsigned int posZ;
        unsigned int negZ;
};
}  // namespace gel
#endif