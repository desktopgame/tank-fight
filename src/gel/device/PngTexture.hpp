#ifndef GEL_DEVICE_PNGTEXTURE_HPP
#define GEL_DEVICE_PNGTEXTURE_HPP
#include "../model/Vector2.hpp"
#include "ITexture.hpp"
namespace gel {

class PngTexture : public ITexture {
       public:
        PngTexture();
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        GLuint getID() const override;
        unsigned char* getData() const override;
        int getWidth() const override;
        int getHeight() const override;
        Vector2 getSize() const override;

       private:
        unsigned int width;
        unsigned int height;
        int depth;
        int colorType;
        int interlaceType;
        unsigned char* data;
        unsigned int textureId;
};
}  // namespace gel
#endif