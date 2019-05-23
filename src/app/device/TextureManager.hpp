#ifndef APP_DEVICE_TEXTUREMANAGER_HPP
#define APP_DEVICE_TEXTUREMANAGER_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <unordered_map>
namespace mygame {
class ITexture;
class TextureManager {
       public:
        TextureManager();
        void loadBmp(const std::string& path);
        void loadPng(const std::string& path);
        std::shared_ptr<ITexture> getTexture(const std::string& path);
        void unload(const std::string& path);

       private:
        std::unordered_map<std::string, std::shared_ptr<ITexture> > texMap;
};
}  // namespace mygame
#endif