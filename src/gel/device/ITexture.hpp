#ifndef APP_DEVICE_ITEXTURE_HPP
#define APP_DEVICE_ITEXTURE_HPP
#include <GLFW/glfw3.h>
#include <string>
namespace gel {
class ITexture {
       public:
        ITexture() = default;
        virtual ~ITexture() = default;
        virtual void load(const std::string& path) = 0;
        virtual void unload(const std::string& path) = 0;
        virtual GLuint getID() const = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
};
}  // namespace gel
#endif