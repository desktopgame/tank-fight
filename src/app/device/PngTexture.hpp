#ifndef APP_DEVICE_PNGTEXTURE_HPP
#define APP_DEVICE_PNGTEXTURE_HPP
#include "ITexture.hpp"
namespace mygame {

class PngTexture : public ITexture {
	public:
	PngTexture();
    void load(const std::string& path) override;
    void unload(const std::string& path) override;
    GLuint getID() const override;
    int getWidth() const override;
    int getHeight() const override;
	private:
	unsigned int width;
	unsigned int height;
	int depth;
	int colorType;
	int interlaceType;
	unsigned char* data;
	unsigned int textureId;
};
}
#endif