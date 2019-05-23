#ifndef APP_DEVICE_BMPTEXTURE_HPP
#define APP_DEVICE_BMPTEXTURE_HPP
#include "ITexture.hpp"
namespace mygame {
class BmpTexture : public ITexture {
       public:
        BmpTexture();
        void load(const std::string& path) override;
        void unload(const std::string& path) override;
        GLuint getTextureID() const override;
        int getWidth() const override;
        int getHeight() const override;

       private:
        void readBMP(const char* filename);
        GLuint tid;
        int width;
        int height;
        unsigned char* data;
};
}  // namespace  mygame
#endif